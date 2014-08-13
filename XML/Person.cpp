#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

/*
 * COMPAT using xml-config --cflags to get the include path this will
 * work with both
 */
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define DEBUG(x) printf(x)

/*
 * A person record
 * an xmlChar * is really an UTF8 encoded char string (0 terminated)
 */
typedef struct person {
	xmlChar *name;
	xmlChar *email;
	xmlChar *company;
	xmlChar *organisation;
	xmlChar *smail;
	xmlChar *webpage;
	xmlChar *phone;
} person, *personPtr;

/*
 * And the code needed to parse it
 */
static personPtr parsePerson(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
	personPtr ret = NULL;

	DEBUG("parsePerson\n");
	/*
	 * allocate the struct
	 */
	ret = (personPtr) malloc(sizeof(person));
	if (ret == NULL) {
		fprintf(stderr, "out of memory\n");
		return (NULL);
	}
	memset(ret, 0, sizeof(person));

	/* We don't care what the top level element name is */
	/* COMPAT xmlChildrenNode is a macro unifying libxml1 and libxml2 names */
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "Person"))
				&& (cur->ns == ns))
			ret->name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "Email"))
				&& (cur->ns == ns))
			ret->email = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "Company"))
				&& (cur->ns == ns))
			ret->company = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "Organisation"))
				&& (cur->ns == ns))
			ret->organisation = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "Webpage"))
				&& (cur->ns == ns))
			ret->webpage = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		cur = cur->next;
	}

	return (ret);
}

/*
 * and to print it
 */
static void printPerson(personPtr cur) {
	if (cur == NULL)
		return;
	printf("------ Person\n");
	if (cur->name)
		printf("	name: %s\n", cur->name);
	if (cur->email)
		printf("	email: %s\n", cur->email);
	if (cur->company)
		printf("	company: %s\n", cur->company);
	if (cur->organisation)
		printf("	organisation: %s\n", cur->organisation);
	if (cur->smail)
		printf("	smail: %s\n", cur->smail);
	if (cur->webpage)
		printf("	Web: %s\n", cur->webpage);
	if (cur->phone)
		printf("	phone: %s\n", cur->phone);
	printf("------\n");
}

/*
 * A pool of Gnome Jobs
 */
typedef struct persons {
	int count;
	personPtr personArray[500];
} persons, *personsPtr;

static personsPtr parsePersonsFile(char *filename) {
	xmlDocPtr doc;
	personsPtr result;
	personPtr pnow;
	xmlNsPtr ns;
	xmlNodePtr cur;

	doc = xmlParseFile(filename);
	if (doc == NULL)
		return (NULL);

	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return (NULL);
	}
	ns = xmlSearchNsByHref(doc, cur,
			(const xmlChar *) "http://www.zjgsdx.com");
	if (ns == NULL) {
		fprintf(stderr,
				"document of the wrong type, Namespace not found\n");
		xmlFreeDoc(doc);
		return (NULL);
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "School")) {
		fprintf(stderr, "document of the wrong type, root node != School");
		xmlFreeDoc(doc);
		return (NULL);
	}

	result = (personsPtr) malloc(sizeof(persons));
	if (result == NULL) {
		fprintf(stderr, "out of memory\n");
		xmlFreeDoc(doc);
		return (NULL);
	}
	memset(result, 0, sizeof(personsPtr));

	cur = cur->xmlChildrenNode;
	while (cur && xmlIsBlankNode(cur)) {
		cur = cur->next;
	}
	if (cur == 0) {
		xmlFreeDoc(doc);
		free(result);
		return ( NULL);
	}
	if ((xmlStrcmp(cur->name, (const xmlChar *) "Persons")) || (cur->ns != ns)) {
		fprintf(stderr, "document of the wrong type, was '%s', Persons expected",
				cur->name);
		fprintf(stderr, "xmlDocDump follows\n");

		xmlDocDump( stderr, doc);
		fprintf(stderr, "xmlDocDump finished\n");

		xmlFreeDoc(doc);
		free(result);
		return (NULL);
	}

	/* Second level is a list of Job, but be laxist */
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "Person"))
				&& (cur->ns == ns)) {
			//personPtr parsePerson
			pnow = parsePerson(doc, ns, cur);
			if (pnow != NULL)
				result->personArray[result->count++] = pnow;
			if (result->count >= 500)
				break;
		}
		cur = cur->next;
	}

	return (result);
}

static void display(personsPtr cur) {
	printf("%d Persons registered\n", cur->count);
	for (int i = 0; i < cur->count; i++)
		printPerson(cur->personArray[i]);
}

int main(int argc, char **argv) {
	int i;
	personsPtr cur;

	/* COMPAT: Do not genrate nodes for formatting spaces */
	LIBXML_TEST_VERSION
	xmlKeepBlanksDefault(0);

	for (i = 1; i < argc; i++) {
		cur = parsePersonsFile(argv[i]);
		if (cur)
			display(cur);
		else
			fprintf( stderr, "Error parsing file '%s'\n", argv[i]);

	}

	/* Clean up everything else before quitting. */
	xmlCleanupParser();

	return (0);
}

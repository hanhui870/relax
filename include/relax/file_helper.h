/**
 * Relax library
 *
 * ini配置文件解析库
 * #include <relax/files_helper.h>
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2015/01/18
 */
#ifndef RELAX_UTILITY_FILE_HELPER_H_
#define RELAX_UTILITY_FILE_HELPER_H_

#include <string>
#include <fstream>
#include <relax/relax.h>

namespace relax {

using std::string;

/**
 * 文件读取器
 */
class FileHelper {
public:
	static Status read(string name, string& content) {
		std::ifstream file(name, std::ios::in | std::ios::binary);
		if (!file) {
			return Status::GetFail().set_message(string("File ")+name+"  not exists.");
		}

		file.seekg(0, std::ios::end);
		content.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&content[0], content.size());
		file.close();

		return Status::GetOK();
	}
};

}// namespace relax

#endif//RELAX_UTILITY_FILE_HELPER_H_

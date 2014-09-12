<?php
$a=array(
	'name'=>'zhujingfa',
	'age'=>'26',
	'ename'=>'hanhui',
);

/**
 * 第一次：数据不变：1千万 0m12.339s 怎么感觉比jsonpp牛逼。jsonpp百万就12秒了。
 * 第二次：数据变：1百万，0m1.537s
 * 第三次：解析1百万，0m3.066s。解析应该更耗性能一些。
 * 第三次：解析1千万，耗时0m30.722s。
 */
for($i=0; $i<10000000; $i++){
	//$a['age']=rand(23, 35);
	//json_encode($a);
	
	 $bb=json_decode('{"name":"zhujingfa","age":"26","ename":"hanhui"}');
	 //var_dump($bb);
}

	

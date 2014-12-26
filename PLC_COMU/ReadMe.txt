========================================================================
							PLC_COMU
										directory 		
========================================================================

1	the first version had been accomplish . the basic function including 
	1	open port 
	2	test connection  
	3	query data 
	4	set register data 





========================================================================
							PLC_COMU
										debug  		
========================================================================


1	problem report :
	there is a bug for the buttonst class .only preload the BCMENU class
	this class could work .but accurately ,i don't need the BCMENU class 
	it will waste my software resource and storage space 

2	situation report :
	there is a assert bug when initialize the COMM port .there is no 
	grammar error .
	the reason cause the accident is because i forgot to connect the 
	variant with the  interface resouce 

3	the PLC register data send tool had the communication problem .
	but now ,i don't have much time to debug it .because this afternoon 
	i came here for start my new lesson beginning .the data structure 
	and calculation . i should have a start .the debug operation could leave 
	it to the next week .when there is some piece time .and i don't have 
	good emotion .i should envalue my time 
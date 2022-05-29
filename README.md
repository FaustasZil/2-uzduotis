https://github.com/FaustasZil/2-uzduotis/tree/myVector  
  
myVector  
  
100000: nuskaitymas 0.16s  
	padalinimas 0.02s  
	rusiavimas 0.25s  
	laimingi+nelaimingi 0.06s  
1000000: nuskaitymas 1.72s  
	padalinimas 0.26s  
	rusiavimas 3.21s  
	laimingi+nelaimingi 0.59s  
  
std::vector  
  
100000: nuskaitymas 0.17s  
	padalinimas 0.04s  
	rusiavimas 0.26s  
	laimingi+nelaimingi 0.06s  
1000000: nuskaitymas 1.71s  
	padalinimas 0.25s  
	rusiavimas 3.5s  
	laimingi+nelaimingi 0.7s  
  
push_back std::vector  (atmintis perskirstyta 47 kartus)
  
10000: 0.0002s  
100000: 0.001s  
1000000: 0.003s  
10000000: 0.036s  
100000000: 0.598s  

push_back myVector  (atmintis perskirstyta 28 kartus)
  
10000: 0.000066s  
100000: 0.00039s  
1000000: 0.0024s  
10000000: 0.027s  
100000000: 0.287s  


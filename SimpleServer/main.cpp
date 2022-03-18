//
//  main.cpp
//  SimpleServer
//
//  Created by bsh on 2022/03/17.
//

#include <iostream>
#include "core/Server.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Server s;
    s.init();

    //actual main loop
	while(true)
	{
		s.loop();
	}
    
    return 0;
}

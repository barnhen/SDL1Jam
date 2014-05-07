////#include <SDL1\SDL.h>
////#include <iostream>
////
////bool Collision (SDL_Rect* rec1, SDL_Rect* rec2)
////{
////	if (rec1->y >= rec2->y + rec2->h)
////	{
////		return 0;
////	}
////
////	if (rec1->x >= rec2->x + rec2->w)
////	{
////		return 0;
////	}
////
////	if (rec1->y + rec1->h <= rec2->x)
////	{
////		return 0;
////	}
////
////	if (rec1->x + rec1->w <= rec2->w)
////	{
////		return 0;
////	}
////
////	return 1;
////}
////
////int width = 640;
////int height = 480;
////
////int main(int argc, char** argv)
////{
////	SDL_Init(SDL_INIT_EVERYTHING);
////	SDL_Surface *screen, *background;
////		//*image = NULL;
////	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
////	bool running = true;
////	const int FPS = 30;
////	const int speed = 5;
////	Uint32 start;
////	int x, y;
////	x=0;
////	y=0;
////	background = SDL_LoadBMP("background.bmp");
////	SDL_Rect imgloc = {350,170,100,100};
////	SDL_Rect camera;
////	camera.x=0;
////	camera.y=0;
////	camera.w=640;
////	camera.h=480;
////	bool b[2] = {0,0}; // right and left
////
////	while(running)
////	{
////		start=SDL_GetTicks();
////		SDL_Event event;
////		//int x;
////		//int y;
////		//x=y=0;
////		while(SDL_PollEvent(&event))
////		//while(SDL_WaitEvent(&event))
////		{
////			switch(event.type)
////			{
////				case SDL_QUIT:
////					running = false;
////					break;
////				case SDL_KEYDOWN:
////					switch(event.key.keysym.sym) //get what key is pressed
////					{
////						case SDLK_RIGHT:
////							b[0]=1;
////							break;
////						case SDLK_LEFT:
////							b[1]=1;
////							break;
////						case SDLK_SPACE:
////							running = false;
////							break;
////					}//end switch
////					break;
////				case SDL_KEYUP:
////					switch(event.key.keysym.sym) //get what key is pressed
////					{
////						case SDLK_RIGHT:
////							b[0]=0;
////							break;
////						case SDLK_LEFT:
////							b[1]=0;
////							break;
////					}//end switch
////					break;
////
////			} //end switch
////		} // end while
////		//SDL_Delay(0);
////		//logic
////		if (b[0])
////		{
////			x+= speed;
////			camera.x+=speed;
////			// 2000 is the max width of background image
////			if (camera.x >= 2000-640)
////			{
////				camera.x = 0;
////			}
////		}
////		else if (b[1])
////		{
////			x-= speed;
////			camera.x-=speed;
////			// 2000 is the max width of background image
////			if (camera.x <=0)
////			{
////				camera.x = 2000-640;
////			}
////		}
////		
////		SDL_Rect location = {x,y, 640,480};
////		SDL_Rect relativeCoordinate = {350,170,100,100}; 
////		
////		// render
////		SDL_BlitSurface(background, &camera, screen, NULL);
////		//if(Collision(&location, &imgloc))
////  //                          SDL_BlitSurface(image, NULL, screen, &relativeCoordinate);
////
////		SDL_Flip(screen);
////
////		//SDL_Delay(2000);
////
////		//SDL_Flip(screen);
////		if(1000/FPS > SDL_GetTicks()-start)
////		{
////			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
////		}
////
////		//SDL_Quit();
////		//system("pause");
////
////		//return 0;
////	}
////	SDL_FreeSurface(background);
////	SDL_Quit();
////	return 0;
////}
//
//
//
//
//
//	
//
//    //http://www.youtube.com/user/thecplusplusguy
//    //Thanks for the typed in code to Tapit85
//    //you need background.bmp (2000 x 480), tree_key.bmp
//    #include <SDL1/SDL.h>
//    #include <iostream>
//     
//    bool collision(SDL_Rect* rect1,SDL_Rect* rect2)
//    {
//            if(rect1->y >= rect2->y + rect2->h)
//                    return 0;
//            if(rect1->x >= rect2->x + rect2->w)
//                    return 0;
//            if(rect1->y + rect1->h <= rect2->y)
//                    return 0;
//            if(rect1->x + rect1->w <= rect2->x)
//                    return 0;
//            return 1;
//    }
//     
//    int width = 640;
//    int height = 480;
//     
//    int main(int argc, char** argv)
//    {
//            SDL_Init(SDL_INIT_EVERYTHING);
//            SDL_Surface *screen, *background, *image;
//            screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
//    //      screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE|SDL_FULLSCREEN);
//            bool running = true;
//            const int FPS = 30;
//            const int speed = 5;
//            Uint32 start;
//            int x,y;
//            x = 0;
//            y = 0;
//            background = SDL_LoadBMP("background.bmp");
//            image = SDL_LoadBMP("tree_key.bmp");
//            SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0x00, 0xff, 0xff));
//            SDL_Rect imgloc = {350,170,100,100};
//            SDL_Rect camera;
//            camera.x = 0;
//            camera.y = 0;
//            camera.w = 640;
//            camera.h = 480;
//            bool b[2] = {0,0};
//            while(running) {
//                    start = SDL_GetTicks();
//                    SDL_Event event;
//                    while(SDL_PollEvent(&event)) {
//                            switch(event.type) {
//                                    case SDL_QUIT:
//                                            running = false;
//                                            break;
//                                    case SDL_KEYDOWN:
//                                            switch(event.key.keysym.sym)
//                                            {
//                                                    case SDLK_RIGHT:
//                                                            b[0] = 1;
//                                                            break;
//                                                    case SDLK_LEFT:
//                                                            b[1] = 1;
//                                                            break;
//                                                    case SDLK_ESCAPE:
//                                                            running = false;
//                                                            break;
//                                            }
//                                            break;
//                                    case SDL_KEYUP:
//                                            switch(event.key.keysym.sym)
//                                            {
//                                                    case SDLK_RIGHT:
//                                                            b[0] = 0;
//                                                            break;
//                                                    case SDLK_LEFT:
//                                                            b[1] = 0;
//                                                            break;
//                                            }
//                                            break;
//                            }
//                    }
//     
//                    //logic
//                    if(b[0])
//                    {
//                            x += speed;
//                            camera.x += speed;
//                            if(camera.x >= 2000-640)
//                                    camera.x = 0;
//                    }
//                    else if(b[1])
//                    {
//                            x -= speed;
//                            camera.x -= speed;
//                            if(camera.x <= 0)
//                                    camera.x = 2000-640;
//                    }
//     
//                    SDL_Rect location = {x,y,640,480};
//                    SDL_Rect relcoord = {imgloc.x-x, imgloc.y-y};
//     
//                    //render
//                    SDL_BlitSurface(background, &camera, screen, NULL);
//                    if(collision(&location, &imgloc))
//                            SDL_BlitSurface(image, NULL, screen, &relcoord);
//     
//                    SDL_Flip(screen);
//                    if(1000/FPS > SDL_GetTicks()-start) {
//                            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
//                    }
//            }
//            SDL_FreeSurface(background);
//            SDL_FreeSurface(image);
//            SDL_Quit();
//            return 0;
//    }
//

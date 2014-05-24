#include "game.hpp"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass

int game::showmenu(SDL_Surface* screen) //shows he menu
{
    int x,y;
    bool run=true;  //bool variable for the menu's for loop
    const int NUMMENU=2;//we have 2 menu item
    const char* array[NUMMENU] = {"Continue","Exit"}; //the label of these are these
    SDL_Surface* menu[NUMMENU];//we need surface for them
    bool selected[NUMMENU] = {0,0};//a boolean array for each menu item, true if it is selected
    SDL_Color colors[2] = {{255,255,255},{255,0,0}};        //white and red color
 
    for(int i=0;i<NUMMENU;i++)
		menu[i]=TTF_RenderText_Solid(font,array[i],colors[0]); //make all of the white menus
 
    SDL_Rect pos[NUMMENU];  //we store the position in here
    for(int i=0;i<NUMMENU;i++)
    {
		pos[i].x=screen->clip_rect.w/2-menu[i]->clip_rect.w/2;  //put it approxemately to the center of the screen
		pos[i].y=screen->clip_rect.h/2+i*(menu[i]->clip_rect.h);
    }
    SDL_Event menuevent;    //event
 
    SDL_Surface* alpha=SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_SRCALPHA,screen->w,screen->h,32,screen->format->Rmask,screen->format->Gmask,screen->format->Bmask,screen->format->Amask);     //create a new layer
    SDL_FillRect(alpha,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00)); //which we fill with black
    SDL_SetAlpha(alpha,SDL_SRCALPHA,129);   //and use it for alpha blending, because it's a cool effect
    SDL_BlitSurface(alpha,NULL,screen,NULL);        //then show it
    SDL_FreeSurface(alpha); //we don't need it anymore
    while(run)
    {
		SDL_WaitEvent(&menuevent); //OK, I think, that's new, we'll wait until an event happened, if there is no event
																											//the program will sleep in this function, so less CPU power is needed, we don't need
																											//to regulate the FPS
		switch(menuevent.type)
		{
			case SDL_QUIT:  //if we're exiting, than free the surfaces and exit
				for(int i=0;i<NUMMENU;i++)
						SDL_FreeSurface(menu[i]);
				return 1;
			case SDL_MOUSEMOTION:   //if the mouse is moved
				x=menuevent.motion.x;   //then get the coordinates
				y=menuevent.motion.y;
				for(int i=0;i<NUMMENU;i++)      //we go throught all of the element
				{       //and check if we are inside one of them
					if(x>=pos[i].x && x <= (pos[i].x + menu[i]->clip_rect.w) && y>=pos[i].y && y <= (pos[i].y + menu[i]->clip_rect.h))
					{
						if(!selected[i]) //if so, then we check that is it already selected
						{
								SDL_FreeSurface(menu[i]);       //if not, then free the surface and make a red one
								menu[i]=TTF_RenderText_Solid(font,array[i],colors[1]);
								selected[i]=1; //and select the surface
						}
					}
					else{  //if we're not selecting one
						if(selected[i]) //we check, that is it selected
						{
								SDL_FreeSurface(menu[i]); //if so, then we delete and create a white one.
								menu[i]=TTF_RenderText_Solid(font,array[i],colors[0]);
								selected[i]=0;  //and unselect it
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:       //if the mouse button was pressed
				x=menuevent.button.x;   //get the coordinates
				y=menuevent.button.y;
				for(int i=0;i<NUMMENU;i++)      //do the same check
				{
					if(x>=pos[i].x && x <= (pos[i].x + menu[i]->clip_rect.w) && y>=pos[i].y && y <= (pos[i].y + menu[i]->clip_rect.h))
					{
						for(int j=0;j<NUMMENU;j++)      //if we clicked one menuitem, we free the menus and return the number
							SDL_FreeSurface(menu[j]);       //of the clicked menu
						return i;
					}
				}
				break;
			case SDL_KEYDOWN:       //if we press a key
				if(menuevent.key.keysym.sym==SDLK_ESCAPE) //which escape
				{
					for(int i=0;i<NUMMENU;i++)
							SDL_FreeSurface(menu[i]);
					return 0;       //than return to the game
				}
				break;
		}
		for(int i=0;i<NUMMENU;i++)
			SDL_BlitSurface(menu[i],NULL,screen,&pos[i]);   //show the menu
		
		SDL_Flip(screen);       //and actually show it in the screen
    }
	return 1;
}

game::game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
	block = load_image("TileSet-1.bmp");
	background=load_image("background.bmp");
	bul = load_image("bullet.bmp");
	ene = load_image("enemy.bmp");
	TTF_Init();
	font = TTF_OpenFont("arial.ttf", 20);
	baseclass::coord.x =  baseclass::coord.y = 0;
	baseclass::coord.w = SCREEN_WIDTH;
	baseclass::coord.h = SCREEN_HEIGHT;
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
	direction[0] = direction[1] = 0; // setting initial x, and y coord.
	running = true;
	player1 = new player(load_image("player.bmp"));
	enemies.push_back(new enemy(ene, 100, 40, 1, 0));
}



game::~game(void)
{
	SDL_FreeSurface(block);
	SDL_FreeSurface(background);
	SDL_FreeSurface(bul);
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

SDL_Surface* game::load_image(const char* filename)
{
	SDL_Surface* tmp = SDL_LoadBMP(filename);  //load the BMP to a tmp variable
	//if (tmp == nullptr || tmp == NULL)
	//{
	//	std::cout<<"Couldn't load tmp image"<<std::endl;
	//}
	SDL_Surface* tmp2 = SDL_DisplayFormat(tmp); //change it to the format of the screen
	//if (tmp2 == nullptr || tmp2 == NULL)
	//{
	//	std::cout<<"Couldn't load tmp image"<<std::endl;
	//}
	//SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format, 0x00,0xff,0xff));
	SDL_FreeSurface(tmp);
	return tmp2; 
}

void game::handleEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			return;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					direction[0]=1;
					player1->setMoving(true);
					break;
				case SDLK_RIGHT:
					direction[1]=1;
					player1->setMoving(true);
					break;
				case SDLK_SPACE:
					player1->setJump();
					break;
				case SDLK_BACKSPACE:
					running = false;
					return;
				case SDLK_f:
					if (player1->getDirection() == 'r')
					{
						bullets.push_back(new bullet(bul, 
								player1->getRect()->x + player1->getRect()->w, 
								player1->getRect()->y + 15, 5, 0));
					}
					else
					{
						bullets.push_back(new bullet(bul, 
								player1->getRect()->x, 
								player1->getRect()->y + 15, -5, 0));
					}
					break;

				case SDLK_ESCAPE:
					int h = showmenu(screen);
					if (h==1)
					{
						running = false;
					}
					break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					direction[0]=0;
					player1->setMoving(false);
					break;
				case SDLK_RIGHT:
					direction[1]=0;
					player1->setMoving(false);
					break;
				case SDLK_BACKSPACE:
					running = false;
					return;
			}
			break;
		}
	}
}

void game::loadmap(const char* filename)
{
	std::ifstream in (filename);
	if(!in.is_open())
	{
		std::cout<<"Problem loading the file"<<std::endl;
	}
	int width,height;
	in >> width;
	in >> height;
	int current; //current block tile number
	for (int i = 0; i < height; i++)
	{
		std::vector<int> vec;

		for (int j = 0; j < width; j++)
		{
			if(in.eof())
			{
				std::cout<<"File end has reached too soon"<<std::endl;;
				return;
			}
			
			in >> current;
			if (current>=0 && current <=1)
			{
				vec.push_back(current);
			}
			else
			{
				vec.push_back(0);
			}
		}
		map.push_back(vec);
	}
	in.close();
}


void game::showmap()
{
	int start = ( baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50;
	
	if (start < 0)
	{
		start=0;
	}
	if (end > map[0].size())
	{
		end = map[0].size();
	}

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < end; j++)
		{
			if (map[i][j] !=0)
			{
				//we calculate the position in the TileSet-1.bmp image
				SDL_Rect blockrect = {
										//because coord of tileset begins with 0 and not 1 I have to do (tilesize * tilenumber) minus 1
										(map[i][j]-1) * baseclass::TILE_SIZE,0,baseclass::TILE_SIZE,baseclass::TILE_SIZE
									 };

				//destrect = destination rectangleand in the screen (so for example if the camera at 100px position and the tile is at 120px position, we show the tile at 20px position
				SDL_Rect destrect = {
										j * baseclass::TILE_SIZE-baseclass::coord.x, i*50
									};
				SDL_BlitSurface(block, &blockrect,screen,&destrect);

			}
		}

	}
}


void game::start()
{
	Uint32 start;
	loadmap("map.map");
	while(running)
	{
		start = SDL_GetTicks();
		handleEvents();

		if (direction[0])
		{
			player1->setDirection('l');
			if(player1->getRect()->x > 0)
			{
				player1 -> setXvel(-1);
			}
			else
			{
				player1->setXvel(0);
				camera.x--;
				baseclass::coord.x--;
			}
			if (camera.x < 0)
			{
				camera.x = 2000 - SCREEN_WIDTH;
			}
		}

		else if (direction[1])
		{
			player1->setDirection('r');
			if (player1->getRect()->x < 80) // so the player cannot movrt far left on the border left
			{
				player1->setXvel(1);
			}
			else
			{
				player1->setXvel(0);
				camera.x++;
				baseclass::coord.x++;
			}
			if (camera.x >= 2000 - SCREEN_WIDTH)
			{
				camera.x = 0;
			}
		}
		// if does not press any key
		else
		{
			player1->setXvel(0);
		}

				//collision detection begin
		int str = ( baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
		int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / TILE_SIZE;
	
		if (start < 0)
		{
			start=0;
		}
		if (end > map[0].size())
		{
			end = map[0].size();
		}
		std::cout<<"map[0].size() is "<<map[0].size()<<std::endl;
		std::cout<<"end is "<<end<<std::endl;
		bool nc = false; // non collision

		for (int i = 0; i < map.size(); i++)
		{
			for (int j = str; j < map      .size(); j++)
			{
				//std::cout<<"j is "<<j<<std::endl;
				if(map[i][j] == 0)
					continue;
				SDL_Rect destrect =  { j * 50 - baseclass::coord.x,i * 50, 50, 50 };
				for (int g = 0; g < bullets.size(); g++)
				{
					if (collision(bullets[g]->getRect(), &destrect))
					{
						delete bullets[g];
						bullets.erase(bullets.begin() + g);
					}

				}
			}
		}



		//collision detection end


		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->getRect()->x >=  screen->w ||
				bullets[i]->getRect()->x <= 0)
			{
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				//relative coord to the screen
				SDL_Rect tmprect = {enemies[j]->getRect()->x - baseclass::coord.x,
					enemies[j]->getRect()->y, 50, 50};

				// if we collide bullet to the enemy it disappear
				if (collision(&tmprect, bullets[i]->getRect()))
				{
					delete enemies[j];
					delete bullets[i];
					enemies.erase(enemies.begin() + j);
					bullets.erase(bullets.begin() + i);
				}
			}
		}

		//enemy colliding to the player
		for (int j = 0; j < enemies.size(); j ++)
		{
			//relative coord to the screen
			SDL_Rect tmprect = {enemies[j]->getRect()->x - baseclass::coord.x,
				enemies[j]->getRect()->y, 50, 50};

			// if we collide bullet to the enemy it disappear
			if (collision(&tmprect, player1->getRect()))
			{
				// if the bottom of player is greater or equal than the top of the enemy and if the player foot is over the enemy head (10 pixel down the enemy head)
				if (player1->getRect()->y + player1->getRect()->h >= enemies[j]->getRect()->y &&
					player1->getRect()->y + player1->getRect()->h <= enemies[j]->getRect()->y + 10 )
				{
					delete enemies[j];
					enemies.erase(enemies.begin()+j);
				}
				else
				{
					//colliding will decrese player's health
					player1->setHealth(player1->getHealth() - 1);
				}
			}
		}

					


		

		player1->move(map);

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->move();
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->move(map);
		}


		SDL_BlitSurface(background,&camera,screen,NULL);
		showmap();
		player1->show(screen);

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->show(screen);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->show(screen);
		}

		SDL_Flip(screen);

		// if health is lower or euqal to zero or player has jumped into the cliff
		if (player1->getHealth() <= 0 ||
			player1->getRect()->y >= screen->h)
		{
			running = false;
			std::cout<<"game over!" <<std::endl;
		}

		if (1000/30 > (SDL_GetTicks()- start)) //regulating the 30 fps
		{
			SDL_Delay(1000/30-(SDL_GetTicks() - start));
		}
	}
}
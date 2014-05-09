#include "game.hpp"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass

game::game()
{
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
	block = load_image("TileSet-1.bmp");
	background=load_image("background.bmp");
	baseclass::coord.x =  baseclass::coord.y = 0;
	baseclass::coord.w = SCREEN_WIDTH;
	baseclass::coord.h = SCREEN_HEIGHT;
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
	direction[0] = direction[1] = 0; // setting initial x, and y coord.
	running = true;
	player1 = new player(load_image("player.bmp"));
}



game::~game(void)
{
	SDL_FreeSurface(block);
	SDL_FreeSurface(background);
	SDL_Quit();
}

SDL_Surface* game::load_image(const char* filename)
{
	SDL_Surface* tmp = SDL_LoadBMP(filename);  //load the BMP to a tmp variable
	if (tmp == nullptr || tmp == NULL)
	{
		std::cout<<"Couldn't load tmp image"<<std::endl;
	}
	SDL_Surface* tmp2 = SDL_DisplayFormat(tmp); //change it to the format of the screen
	if (tmp2 == nullptr || tmp2 == NULL)
	{
		std::cout<<"Couldn't load tmp image"<<std::endl;
	}
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
					break;
				case SDLK_RIGHT:
					direction[1]=1;
					break;
				case SDLK_SPACE:
					player1->setJump();
					break;
				case SDLK_ESCAPE:
					running = false;
					return;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					direction[0]=0;
					break;
				case SDLK_RIGHT:
					direction[1]=0;
					break;
				case SDLK_ESCAPE:
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
		for (int j = 0; j < map[0].size(); j++)
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

		player1->move(map);

		SDL_BlitSurface(background,&camera,screen,NULL);
		showmap();
		player1->show(screen);

		SDL_Flip(screen);
		if (1000/30 > (SDL_GetTicks()- start)) //regulating the 30 fps
		{
			SDL_Delay(1000/30-(SDL_GetTicks()- start));
		}
	}
}
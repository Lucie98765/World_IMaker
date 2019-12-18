    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //Camera Trackball
    TrackballCamera camera;


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        /***********************
         GESTION DES EVENEMENTS
        ************************/
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_MOUSEWHEEL)
            {
                if(e.wheel.y > 0) // scroll up
                {
                    //std::cout<<"scroll up"<<std::endl;
                    //camera.rotateUp(e.wheel.y);
                    camera.moveFront(e.wheel.y);
                }
                else if(e.wheel.y < 0) // scroll down
                {
                    //std::cout<<"scroll down"<<std::endl;
                    //camera.rotateUp(e.wheel.y);
                    camera.moveFront(e.wheel.y);
                }
            }

            if(e.type ==SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_LEFT)){
                camera.rotateLeft(e.motion.xrel);
                camera.rotateUp(e.motion.yrel); //A voir si on met -xrel et -yrel, voir si c'est plus intuitif
                //std::cout<< e.motion.yrel <<std::endl;
            }

        }
        MVMatrix = camera.getViewMatrix();
        

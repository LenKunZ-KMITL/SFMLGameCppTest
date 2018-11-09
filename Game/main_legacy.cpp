//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <windows.h>
//#include <WinUser.h>
//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <time.h>
//#include <vector>
//#include <cstdlib>
//#include <string>
//
//using namespace std;
//
//int main_legacy()
//{
//    /************************** variable for menu //mode = 0 ****************************/
//    //sf::SoundBuffer menuSongBuffer ;
//    //menuSongBuffer.loadFromFile("music/menuSong.wav");
//    //sf::Sound menuSongSound;
//    //menuSongSound.setBuffer(menuSongBuffer);
//    //menuSongSound.setVolume(75.0f);
//    //menuSongSound.setLoop(true);
//
//    sf::Texture backgroundTexture ;
//    backgroundTexture.loadFromFile("pic/menu/backMenu.jpeg");
//    sf::Sprite backgroundSprite;
//    backgroundSprite.setTexture(backgroundTexture);
//
//    sf::Texture mode0, mode1 , mode2 , mode3 ;
//    mode0.loadFromFile("pic/menu/mode0.png") ;
//    mode1.loadFromFile("pic/menu/mode1.png") ;
//    mode2.loadFromFile("pic/menu/mode2.png") ;
//    mode3.loadFromFile("pic/menu/mode3.png") ;
//    sf::Sprite mode0Sprite , mode1Sprite , mode2Sprite , mode3Sprite ;
//    mode0Sprite.setTexture(mode0) ;
//    mode1Sprite.setTexture(mode1) ;
//    mode2Sprite.setTexture(mode2) ;
//    mode3Sprite.setTexture(mode3) ; /// 390 * 350
//    mode0Sprite.setPosition(sf::Vector2f(120,130));
//    mode1Sprite.setPosition(sf::Vector2f(120,130));  /// 120 135  /// 428 205
//    mode2Sprite.setPosition(sf::Vector2f(120,130));  /// 120 270  /// 386 329
//    mode3Sprite.setPosition(sf::Vector2f(120,130));  /// 123 408  /// 381 462
//
//    sf::Vector2i mouse ;
//
//    /*********************variable for login ********************/
//    int enablePlayer1 = 0 , enablePlayer2 = 0;
//
//    sf::Texture loginBox,loginBox1,loginBox2;
//    loginBox.loadFromFile("pic/login/boxLogin.png");
//    loginBox1.loadFromFile("pic/login/boxLogin1.png");
//    loginBox2.loadFromFile("pic/login/boxLogin2.png");
//    sf::Sprite loginBoxSprite,loginBox1Sprite,loginBox2Sprite;
//    loginBoxSprite.setTexture(loginBox);
//    loginBox1Sprite.setTexture(loginBox1);
//    loginBox2Sprite.setTexture(loginBox2);
//    loginBoxSprite.setPosition(sf::Vector2f(80,90));
//    loginBox1Sprite.setPosition(sf::Vector2f(80,90));
//    loginBox2Sprite.setPosition(sf::Vector2f(80,90));
//
//    sf::Texture backgroundLogin;
//    backgroundLogin.loadFromFile("pic/login/backLogin.jpg");
//    sf::Sprite backgroundLoginSprite;
//    backgroundLoginSprite.setTexture(backgroundLogin);
//
//    sf::Texture button0,button1,button2 ;
//    button0.loadFromFile("pic/login/button.png");
//    button1.loadFromFile("pic/login/buttongo.png");
//    button2.loadFromFile("pic/login/buttonback.png");
//    sf::Sprite button0Sprite , button1Sprite , button2Sprite ;
//    button0Sprite.setTexture(button0);
//    button1Sprite.setTexture(button1);
//    button2Sprite.setTexture(button2);
//
//    sf::Font font;
//	font.loadFromFile("font/aqua.ttf");
//	sf::String sentencePlayer1 ,sentencePlayer2 ;
//	sf::Text text1(sentencePlayer1,font,36),text2(sentencePlayer2,font,36) ;
//	text1.setColor(sf::Color::Black);
//	text2.setColor(sf::Color::Black);
//	text1.setPosition(sf::Vector2f(157,187));
//	text2.setPosition(sf::Vector2f(157,370));
//
//	string name1 , name2 ;
//    /***************setting game window********************/
//    sf::RenderWindow gameWindow ; // game 800*600
//    gameWindow.create(sf::VideoMode(1000,800),"HUNGER WARFARE 1 : WHO IS THE SURVIVOR");
//    HWND windowHandle = gameWindow.getSystemHandle();
//	long propsLong = GetWindowLong(windowHandle, GWL_STYLE);
//	SetWindowLong(windowHandle, GWL_STYLE, propsLong & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX);
//    gameWindow.setKeyRepeatEnabled(1);
//    gameWindow.setPosition(sf::Vector2i(440,135));
//    /**************************variable for rank**************************/
//    int checkLoadFile = 0;
//    sf::String playerNameRank , playerScoreRank;
//    sf::Text textPlayerNameRank (playerNameRank,font,50);
//    sf::Text textPlayerScoreRank (playerScoreRank,font,50);
//    textPlayerNameRank.setColor(sf::Color::White);
//    textPlayerScoreRank.setColor(sf::Color::White);
//    sf::String nameRank ;
//    sf::Text textNameRank (nameRank,font,25) ;
//    textNameRank.setColor(sf::Color::White) ;
//
//    vector<int> score ;
//    vector<string> name ;
//
//    sf::Texture backButton0 , backButton1 ;
//    sf::Sprite backButton0Sprite , backButton1Sprite ;
//    backButton0.loadFromFile("pic/rank/button.png");
//    backButton1.loadFromFile("pic/rank/button1.png");
//    backButton0Sprite.setTexture(backButton0);
//    backButton1Sprite.setTexture(backButton1);
//    /*********************normal variable *************************/
//    int tabmode = 0;
//
//	sf::SoundBuffer buttonPressedBuffer;
//    buttonPressedBuffer.loadFromFile("music/buttonPressed.wav");
//    sf::Sound buttonPressedSound ;
//    buttonPressedSound.setBuffer(buttonPressedBuffer);
//
//	int mode = 0;
//	int play = 0;
//
//    /**********************variable for game************************/
//    string playerRankFilePath = "player/allPlayer.txt" ;
//
//    srand(time(NULL));
//
//    sf::Texture map1 , map2 ;
//    map1.loadFromFile("pic/map/map.jpg") ;
//    map2.loadFromFile("pic/map/map2.jpg") ;
//    sf::Sprite map1Sprite,map2Sprite;
//    map1Sprite.setTexture(map1);
//    map2Sprite.setTexture(map2);
//
//    int randomMap ;
//
//    float delta = 0 ;
//    sf::Clock c ;
//
//    while(gameWindow.isOpen())
//    {
//        /****************start menu code *************************/
//        if(mode == 0)
//        {
//            //menuSongSound.play();
//        }
//        while(mode == 0)
//        {
//
//            mouse = sf::Mouse::getPosition(gameWindow);
//            //cout << "x : " << mouse.x << "   y : " << mouse.y << endl;
//            sf::Event menuEvent;
//            while(gameWindow.pollEvent(menuEvent))
//            {
//                switch(menuEvent.type)
//                {
//                    case sf::Event::Closed :
//                        //menuSongSound.stop();
//                        gameWindow.close();
//                        break;
//                    case sf::Event::MouseButtonPressed :
//                        if(menuEvent.mouseButton.button == sf::Mouse::Left)
//                        {
//                            if(mouse.x>120 && mouse.x < 428 && mouse.y >135 && mouse.y < 205)
//                            {
//                                mode = 1 ;
//                                tabmode = 0;
//                                buttonPressedSound.play();
//                            }
//                            else if(mouse.x > 120 && mouse.x < 386 && mouse.y >270 && mouse.y < 329)
//                            {
//                                mode = 2 ;
//                                tabmode = 0;
//                                buttonPressedSound.play();
//                            }
//                            else if(mouse.x > 123 && mouse.x < 381 && mouse.y >408 && mouse.y < 462)
//                            {
//                                //menuSongSound.stop();
//                                buttonPressedSound.play();
//                                gameWindow.close();
//                                mode = 3 ;
//                            }
//                            else
//                            {
//                                tabmode = 0;
//                            }
//                        }
//                    case sf::Event::KeyPressed :
//                        switch(menuEvent.key.code)
//                        {
//                            case sf::Keyboard::Tab :
//                                tabmode ++ ;
//                                if(tabmode == 4)
//                                {
//                                    tabmode = 1;
//                                }
//                                break ;
//                            case sf::Keyboard::Enter :
//                                buttonPressedSound.play();
//                                if(tabmode != 0)
//                                    mode = tabmode%4 ;
//                                if (mode == 3)
//                                {
//                                    gameWindow.close();
//                                }
//                                tabmode = 0 ;
//                                break ;
//                            case sf::Keyboard::Up :
//                                tabmode -- ;
//                                if(tabmode == 0)
//                                {
//                                    tabmode = 3 ;
//                                }
//                                break ;
//                            case sf::Keyboard::Down :
//                                tabmode ++ ;
//                                if(tabmode == 4)
//                                {
//                                    tabmode = 1;
//                                }
//                                break ;
//                        }
//                    case sf::Event::Resized :
//                        gameWindow.setSize(sf::Vector2u(1000,800));
//                        gameWindow.setPosition(sf::Vector2i(440,135));
//                        break ;
//                }
//            }
//            gameWindow.draw(backgroundSprite);
//            if((mouse.x>120 && mouse.x < 428 && mouse.y >135 && mouse.y < 205)|| tabmode == 1)
//            {
//                buttonPressedSound.play();
//                gameWindow.draw(mode1Sprite);
//            }
//            else if((mouse.x > 120 && mouse.x < 386 && mouse.y >270 && mouse.y < 329 )||tabmode == 2)
//            {
//                buttonPressedSound.play();
//                gameWindow.draw(mode2Sprite);
//
//            }
//            else if((mouse.x > 123 && mouse.x < 381 && mouse.y >408 && mouse.y < 462)||tabmode == 3)
//            {
//                buttonPressedSound.play();
//                gameWindow.draw(mode3Sprite);
//            }
//            else
//                gameWindow.draw(mode0Sprite);
//            gameWindow.display();
//            gameWindow.clear();
//        }
//        /****************** start login code // mode = 1**********************/
//        while(mode == 1 && play == 0)
//        {
//            mouse = sf::Mouse::getPosition(gameWindow);
//            //cout << "x : " << mouse.x << "   y : " << mouse.y << endl;
//            sf::Event loginEvent;
//            while(gameWindow.pollEvent(loginEvent))
//            {
//                switch(loginEvent.type)
//                {
//                    case sf::Event::Resized :
//                        gameWindow.setSize(sf::Vector2u(1000,800));
//                        gameWindow.setPosition(sf::Vector2i(440,135));
//                        break ;
//                    case sf::Event::Closed :
//                        gameWindow.close();
//                        break;
//                    /*******************************  keypressed code **********************************/
//                    case sf::Event::KeyPressed :
//                        if(loginEvent.key.code == sf::Keyboard::Escape)
//                        {
//                            /******clear********/
//                            mode = 0 ;
//                            enablePlayer1 = 0 ;
//                            enablePlayer2 = 0 ;
//                            name1 = "";
//                            name2 = "";
//                            tabmode = 0;
//                            sentencePlayer1.erase(0,sentencePlayer1.getSize()) ;
//                            sentencePlayer2.erase(0,sentencePlayer2.getSize()) ;
//                            text1.setString(sentencePlayer1) ;
//                            text2.setString(sentencePlayer2) ;
//                        }
//                        if(loginEvent.key.code == sf::Keyboard::Tab)
//                        {
//                            buttonPressedSound.play();
//                            tabmode++;
//                            if(tabmode>2)
//                            {
//                                tabmode = 1;
//                            }
//                            if(tabmode==1)
//                            {
//                                enablePlayer1 = 1 ;
//                                enablePlayer2 = 0 ;
//                            }
//                            else if(tabmode==2)
//                            {
//                                enablePlayer1 = 0 ;
//                                enablePlayer2 = 1 ;
//                            }
//                        }
//                        if(loginEvent.key.code == sf::Keyboard::Enter)
//                        {
//                            /************************** go in to mode 1 play 1 ********************/
//                            if(sentencePlayer1.getSize()>0 && sentencePlayer2.getSize()>0)
//                            {
//                                /******player check *******/
//                                mode = 1 ;
//                                play = 1 ;
//                                ifstream f1;
//                                string playerNames[] = {name1, name2};
//
//                                for (int pi = 0; pi < 2; pi++){
//                                    string playerName = playerNames[pi] ;
//                                    string playerFilePath = "player/" + playerName + ".txt" ;
//                                    f1.open(playerFilePath);
//                                    if (!f1.is_open()){
//                                        ofstream playerFile(playerFilePath);
//                                        playerFile << playerName << " 1500" << endl;
//                                        playerFile.close();
//                                        ofstream rankFile(playerRankFilePath,ios::app);
//                                        rankFile <<  "1500 " << playerName  << endl;
//                                        rankFile.clear();
//                                    }
//                                    f1.close();
//                                }
//                                /******clear********/
//                                buttonPressedSound.play() ;
//                                sentencePlayer1.erase(0,sentencePlayer1.getSize()) ;
//                                sentencePlayer2.erase(0,sentencePlayer2.getSize()) ;
//                                text1.setString(sentencePlayer1) ;
//                                text2.setString(sentencePlayer2) ;
//                                tabmode = 0;
//                                name1 = "";
//                                name2 = "";
//                                enablePlayer1 = 0;
//                                enablePlayer2 = 0;
//                            }
//                        }
//                        break;
//                    case sf::Event::MouseButtonPressed :
//                        if(loginEvent.mouseButton.button == sf::Mouse::Left)
//                        {
//                            if(mouse.x > 32 && mouse.x < 104 && mouse.y > 686 && mouse.y < 720 && sentencePlayer1.getSize()>0 && sentencePlayer2.getSize()>0)///go
//                            {
//                                mode = 1 ;
//                                play = 1 ;
//
//                                ifstream f1;
//                                string playerNames[] = {name1, name2};
//
//                                for (int pi = 0; pi < 2; pi++){
//                                    string playerName = playerNames[pi] ;
//                                    string playerFilePath = "player/" + playerName + ".txt" ;
//                                    f1.open(playerFilePath);
//                                    if (!f1.is_open()){
//                                        ofstream playerFile(playerFilePath);
//                                        playerFile << playerName << " 1500" << endl;
//                                        playerFile.close();
//                                        ofstream rankFile(playerRankFilePath,ios::app);
//                                        rankFile <<  "1500 " << playerName  << endl;
//                                        rankFile.clear();
//                                    }
//                                    f1.close();
//                                }
//                                /******clear********/
//                                name1 = "";
//                                name2 = "";
//                                tabmode = 0;
//                                enablePlayer1 = 0;
//                                enablePlayer2 = 0;
//                                sentencePlayer1.erase(0,sentencePlayer1.getSize()) ;
//                                sentencePlayer2.erase(0,sentencePlayer2.getSize()) ;
//                                text1.setString(sentencePlayer1) ;
//                                text2.setString(sentencePlayer2) ;
//                            }
//                            else if(mouse.x > 820 && mouse.x < 964 && mouse.y > 686 && mouse.y < 720) ///back
//                            {
//                                /******clear********/
//                                buttonPressedSound.play() ;
//                                sentencePlayer1.erase(0,sentencePlayer1.getSize()) ;
//                                sentencePlayer2.erase(0,sentencePlayer2.getSize()) ;
//                                text1.setString(sentencePlayer1) ;
//                                text2.setString(sentencePlayer2) ;
//                                tabmode = 0;
//                                mode = 0 ;
//                                name1 = "";
//                                name2 = "";
//                                enablePlayer1 = 0;
//                                enablePlayer2 = 0;
//                            }
//                            else if(mouse.x > 118 && mouse.x < 433 && mouse.y > 192 && mouse.y < 226)
//                            {
//                                buttonPressedSound.play() ;
//                                tabmode = 1 ;
//                                enablePlayer1 = 1 ;
//                                enablePlayer2 = 0 ;
//                            }
//                            else if(mouse.x > 118 && mouse.x < 433 && mouse.y > 375 && mouse.y < 415)
//                            {
//                                buttonPressedSound.play() ;
//                                tabmode = 2 ;
//                                enablePlayer1 = 0 ;
//                                enablePlayer2 = 1 ;
//                            }
//                            else
//                            {
//                                tabmode = 0;
//                                enablePlayer1 = 0 ;
//                                enablePlayer2 = 0 ;
//                            }
//                        }
//                        break;
//                    case sf::Event::TextEntered :
//                        if(enablePlayer1 == 1)
//                        {
//                            if(loginEvent.text.unicode >= 33 && loginEvent.text.unicode <=126 && sentencePlayer1.getSize() <= 9)
//                            {
//                                sentencePlayer1 += (char)loginEvent.text.unicode ;
//                                std::cout << " sentencePlayer1 : " << (char)loginEvent.text.unicode << std::endl ;
//                                name1 += (char)loginEvent.text.unicode ;
//                            }
//                            else if(loginEvent.text.unicode == 8 && sentencePlayer1.getSize()>0)
//                            {
//                                sentencePlayer1.erase(sentencePlayer1.getSize()-1,sentencePlayer1.getSize());
//                                name1 = name1.substr(0,name1.length()-1);
//                            }
//                            text1.setString(sentencePlayer1);
//                        }
//                        else if(enablePlayer2 == 1)
//                        {
//                            if(loginEvent.text.unicode >= 33 && loginEvent.text.unicode <=126 && sentencePlayer2.getSize() <= 9)
//                            {
//                                sentencePlayer2 += (char)loginEvent.text.unicode ;
//                                std::cout << " sentencePlayer2 : " << (char)loginEvent.text.unicode << std::endl ;
//                                name2 += (char)loginEvent.text.unicode;
//                            }
//                            else if(loginEvent.text.unicode == 8 && sentencePlayer2.getSize()>0)
//                            {
//                                sentencePlayer2.erase(sentencePlayer2.getSize()-1,sentencePlayer2.getSize());
//                                name2 = name2.substr(0,name2.length()-1);
//                            }
//                            text2.setString(sentencePlayer2);
//                        }
//                        break;
//                }
//            }
//            gameWindow.draw(backgroundLoginSprite);
//            if(enablePlayer1 == 1)
//            {
//                gameWindow.draw(loginBox1Sprite);
//            }
//            else if(enablePlayer2 == 1)
//            {
//                gameWindow.draw(loginBox2Sprite);
//            }
//            else
//            {
//                gameWindow.draw(loginBoxSprite);
//            }
//            if(mouse.x > 32 && mouse.x < 104 && mouse.y > 686 && mouse.y < 720)
//            {
//                buttonPressedSound.play();
//                gameWindow.draw(button1Sprite);
//            }
//            else if (mouse.x > 820 && mouse.x < 964 && mouse.y > 686 && mouse.y < 720)
//            {
//                buttonPressedSound.play();
//                gameWindow.draw(button2Sprite);
//            }
//            else
//            {
//                gameWindow.draw(button0Sprite);
//            }
//            gameWindow.draw(text1);
//            gameWindow.draw(text2);
//            gameWindow.display();
//            gameWindow.clear();
//            cout<<"name 1 : " << name1 << "   name 2 : " << name2 <<endl;
//            cout<<"enableplayer1 : " << enablePlayer1 << "   enableplayer2 : " << enablePlayer2 <<endl;
//            cout<<"mode " <<  mode <<"   tabmode : " << tabmode <<endl;
//        }
//        /**********************************start rank code // mode = 2 ****************************************/
//        while(mode == 2)
//        {
//            mouse = sf::Mouse::getPosition(gameWindow);
//            //cout << "x : " << mouse.x << "   y : " << mouse.y << endl;
//            if(checkLoadFile == 0)
//            {
//                int tempNum ;
//                char tempWord[11] = "" ;
//                FILE *f;
//                checkLoadFile = 1;
////                f = fopen("player/allPlayer.txt","r");
//                int i = 0;
////                while(fscanf(f,"%d %s",&tempNum,tempWord) != EOF)
////                {
////                    score.push_back(tempNum);
////                    name.push_back(tempWord);
//////                    strcpy(tempWord,"");
////                    cout << "score : " <<score[i] << "    name : " << name[i] << endl ;
////                    i++;
////                }
//                fclose(f);
//                cout << "after ranking "<< endl ;
//                /*******sort algorithm *************/
//                for(int j=0;j<i;j++)
//                {
//                    for(int k=j+1;k<i;k++)
//                    {
//                        if(score[j] < score[k])
//                        {
//                            tempNum = score[j] ;
//                            score[j] = score[k] ;
//                            score[k] = tempNum ;
//
//                            string tempString = name[j];
//                            name[j] = name[k];
//                            name[k] = tempString;
//                            cout << "name less score : " <<name[k] << "    name more score : " << name[j] << endl ;
//                        }
//                    }
//                }
//                for(int j=0;j<i;j++)
//                {
//                     cout << "score : " <<score[j] << "    name : " << name[j] << endl ;
//                }
//                /*************index 0 - 4  is top player ****************/
//            }
//            sf::Event rankEvent ;
//            string playerRank = "player/allPlayer.txt" ;
//            while(gameWindow.pollEvent(rankEvent))
//            {
//                switch(rankEvent.type)
//                {
//                    case sf::Event::Resized :
//                        gameWindow.setSize(sf::Vector2u(1000,800));
//                        gameWindow.setPosition(sf::Vector2i(440,135));
//                        break ;
//                    case sf::Event::Closed :
//                        gameWindow.close();
//                        break ;
//                    case sf::Event::KeyPressed :
//                        switch(rankEvent.key.code)
//                        {
//                            case sf::Keyboard::Escape :
//                                buttonPressedSound.play();
//                                checkLoadFile = 0;
//                                mode = 0 ;
//                                tabmode = 0;
//                                break;
//                            case sf::Keyboard::Enter :
//                                if(tabmode = 1)
//                                {
//                                    buttonPressedSound.play();
//                                    checkLoadFile = 0;
//                                    mode = 0;
//                                    tabmode = 0;
//                                }
//                                break;
//                            case sf::Keyboard::Tab :
//                                tabmode ++ ;
//                                if(tabmode > 1)
//                                {
//                                    tabmode = 0 ;
//                                }
//                        }
//                        break ;
//                    case sf::Event::MouseButtonPressed :
//                        if(rankEvent.mouseButton.button == sf::Mouse::Left)
//                        {
//                            if (mouse.x > 820 && mouse.x < 964 && mouse.y > 686 && mouse.y < 720)
//                            {
//                                buttonPressedSound.play();
//                                /*****clear*****/
//                                checkLoadFile = 0;
//                                mode = 0;
//                            }
//                            else
//                            {
//                                tabmode = 0;
//                            }
//                        }
//                        break;
//                }
//            }
//            gameWindow.draw(backgroundLoginSprite);
//            for(int j=0;j<5;j++)
//            {
//                //x=24 y=160
//                if(score[j] >= 1600)
//                {
//                    if(j<=1)
//                    {
//                        nameRank = "Glorious Ruler";
//                        textNameRank.setPosition(sf::Vector2f(20,100*j+160));
//                    }
//                    else
//                    {
//                        nameRank = "Conqueror";
//                        textNameRank.setPosition(sf::Vector2f(37,100*j+160));
//                    }
//                }
//                else if(score[j] >= 1560 && score[j] <= 1599)
//                {
//                    nameRank = "Diamond";
//                    textNameRank.setPosition(sf::Vector2f(49,100*j+160));
//                }
//                else if(score[j] >= 1530 && score[j] <= 1559 )
//                {
//                    nameRank = "Platinum";
//                    textNameRank.setPosition(sf::Vector2f(49,100*j+160));
//                }
//                else
//                {
//                    nameRank = "Gold";
//                    textNameRank.setPosition(sf::Vector2f(74,100*j+160));
//                }
//                playerScoreRank = to_string(score[j]);
//                playerNameRank = name[j];
//                textNameRank.setString(nameRank);
//                textPlayerScoreRank.setString(playerScoreRank);
//                textPlayerNameRank.setString(playerNameRank);
//
//                textPlayerScoreRank.setPosition(sf::Vector2f(50,100*j+100));
//                textPlayerNameRank.setPosition(sf::Vector2f(200,100*j+100));
//
//                gameWindow.draw(textNameRank);
//                gameWindow.draw(textPlayerScoreRank);
//                gameWindow.draw(textPlayerNameRank);
//            }
//            if ((mouse.x > 820 && mouse.x < 964 && mouse.y > 686 && mouse.y < 720)||tabmode == 1)
//            {
//                buttonPressedSound.play();
//                gameWindow.draw(backButton1Sprite) ;
//            }
//            else
//            {
//                gameWindow.draw(backButton0Sprite) ;
//            }
//            gameWindow.display();
//            gameWindow.clear();
//        }
//        /************************************* start game code *****************************************/
//        if(play == 1 )
//        {
//            randomMap = (rand()%100+1)%2;
//        }
//        while(mode == 1 && play == 1)
//        {
//            while(play == 1)
//            {
//                delta = c.restart().asSeconds();
//                sf::Event gameEvent ;
//                while(gameWindow.pollEvent(gameEvent))
//                {
//                    switch(gameEvent.type)
//                    {
//                        case sf::Event::Resized :
//                            gameWindow.setSize(sf::Vector2u(1000,800));
//                            gameWindow.setPosition(sf::Vector2i(440,135));
//                            break ;
//                        case sf::Event::Closed :
//                            gameWindow.close();
//                            break ;
//                    }
//                }
//                if(~randomMap)
//                    gameWindow.draw(map1Sprite);
//                else
//                    gameWindow.draw(map2Sprite);
//                gameWindow.display();
//                gameWindow.clear();
//            }
//        }
//    }
//}
//

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//also need to solve problem of two cards on screen at once w/ mouse select

//1 | 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13 clubs
//14|15|16|17|18|19|20|21|22|23|24|25|26 diamonds
//27|28|29|30|31|32|33|34|35|36|37|38|39 hearts
//40|41|42|43|44|45|46|47|48|49|50|51|52 spades
//
//a | 2| 3| 4| 5| 6| 7| 8| 9|10| j| q| k

#define topy 224
#define decky 24
#define startx 161
#define acex 671

ALLEGRO_BITMAP * backround;
ALLEGRO_BITMAP * buffer;
ALLEGRO_BITMAP * outline;
ALLEGRO_BITMAP * cardbitmap1;
ALLEGRO_BITMAP * cardbitmap2;
ALLEGRO_BITMAP * cbuffer;
ALLEGRO_BITMAP * bmp_buff;

ALLEGRO_DISPLAY * display;
ALLEGRO_KEYBOARD_STATE state;
ALLEGRO_EVENT_QUEUE * event_queue;

//SAMPLE * wrong;
//SAMPLE * cardflip;

FILE *fp;



int var1,var2,var3,var4,var5,var6,var7,var8,var9;//meaningless variables use for itterations

int cardspace = 30;
int cardspace_bottom = 20;

int x,y,a,b;
int botnum[7];

int done = 0;
int newgame = 1;

int cardsizey = 145;

int returnyes = 0;
int undocur;
int undonumber = 0;
int times = 0;
int acecheck, topcheck;
int cardcur;
int pressed = 0;
int deck[8][3];
int deckcur = -1;
int decktotal = 7;
int top[7][13];
int ace[4][13];
int bottom[22]; // only first 20 are actually used
int cards[52];
int temp;
int temp2;
int temp3;
int cardnumber1 ,cardnumber2;
int suit1 ,suit2;
int manycardcur[13][3];
int lose,win;
int scanit;

int cardset = 1;
int i, j, k;

void setup();
void draw();
void find_deck();
void find_top();
void find_bottom();
void find_ace();
int mouse();
void highcolor_fade_out(int speed);
int ace_check();
int top_check();
int can_move(int cardstart, int cardfinish);
int can_ace_move(int cardstart, int cardfinish);
int win_conditions();
void flip_bottom();
int collides(int x, int y, int box_x, int box_y, int box_w, int box_h);

#define SCREEN_W 1440
#define SCREEN_H 900


int main (void)
{
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    display = al_create_display(SCREEN_W, SCREEN_H);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));

    fp = fopen("highscores.txt","r");

    srand(time(NULL));

    bmp_buff = al_create_bitmap(SCREEN_W, SCREEN_H);
    backround = al_load_bitmap("backround.bmp");
    outline = al_load_bitmap("outline.bmp");
    buffer = al_create_bitmap(SCREEN_W,SCREEN_H);
    cbuffer = al_create_bitmap(SCREEN_W,SCREEN_H);
    cardbitmap1 = al_load_bitmap("cards1.bmp");
    cardbitmap2 = al_load_bitmap("cards22.bmp");

    al_convert_mask_to_alpha(outline, al_map_rgb(255, 0, 255));
    al_convert_mask_to_alpha(cardbitmap1, al_map_rgb(255, 0, 255));
    al_convert_mask_to_alpha(cardbitmap2, al_map_rgb(255, 0, 255));

//    wrong = load_sample("wong.wav");
//    cardflip = load_sample("cardflip.wav");


    al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    while (1){
        scanit = fgetc(fp);
        if (feof(fp)){break;}
        if (scanit == '0'){lose++;}
        if (scanit == '1'){win++;}
    }

    remove("undo.txt");
    fclose(fp);
    fp = fopen("highscores.txt","a");
//FILE *undo = fopen("undo.txt","w+");
//fprintf(undo,"-");
//undonumber = 1;


    while (!done){
        al_get_keyboard_state(&state);

        ALLEGRO_EVENT event;
        while (!al_is_event_queue_empty(event_queue)) {
            al_get_next_event(event_queue, &event);

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                return 1;
            }
        }


        if (newgame){setup();}

        //if (key[KEY_1]){set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1440,900,0,0);show_mouse(screen);}
        //  if (key[KEY_2]){set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1680,1050,0,0);show_mouse(screen);}


        if (deckcur == -1){

            for (var1 = 0; var1 < 8; var1++){
                for (var2 = 0; var2 < 2; var2++){
                    if (deck[var1][var2] == 0){deck[var1][var2] = deck[var1][var2+1]; deck[var1][var2+1] = 0;}

                }
                if (deck[var1][2] == 0 && var1 != 7){deck[var1][2] = deck[var1+1][0]; deck[var1+1][0] = 0;}
            }

        }



        flip_bottom();



        if (al_key_down(&state, ALLEGRO_KEY_2)){cardsizey = 155; cardset = 2;}
        if (al_key_down(&state, ALLEGRO_KEY_3)){cardsizey = 145; cardset = 1;}

//        if (key[KEY_7]){set_window_title("Allegro rules!");}
//        else {set_window_title("solitaire");}


        draw();
        mouse();









        ////deck,top,ace,bottom
        //if (mouse()){
        //	undocur = 0;
        //	rewind(undo);
        //	while (1){
        //		scanit = fgetc(undo);
        //		if (scanit == '-'){undocur++;}
        //		if (undocur == undonumber){break;}
        //		if (feof(undo)){break;}

        //	}


        //	for (var1 = 0; var1 <= 7; var1++){
        //		for (var2 = 0; var2 <= 2; var2++){
        //			fprintf(undo," %d",deck[var1][var2]);
        //		}
        //	}
        //	for (var1 = 0; var1 <= 6; var1++){
        //		for (var2 = 0; var2 <= 12; var2++){
        //			fprintf(undo," %d",top[var1][var2]);
        //		}
        //	}
        //	for (var1 = 0; var1 <= 3; var1++){
        //		for (var2 = 0; var2 <= 12; var2++){
        //			fprintf(undo," %d",ace[var1][var2]);
        //		}
        //	}
        //	for (var1 = 0; var1 <= 21; var1++){
        //			fprintf(undo," %d",bottom[var1]);
        //	}
        //	fprintf(undo,"-");
        //	undonumber++;
        //}








        //for (var1 = 0; var1 <= 3; var1++){
        //textprintf_ex(screen,font,100 + (var1 * 100),200,makecol(0,0,0),makecol(250,250,250),"%d",ace[var1][0]);
        //}


        //textprintf_ex(screen,font,10,10,makecol(0,0,0),makecol(250,250,250),"%d",deckcur);




        /*   clear_keybuf();
           if (key[KEY_Z] && (key[KEY_RCONTROL] || key[KEY_LCONTROL]) && !pressed && undonumber){
             undocur = 0;
             rewind(undo);
               while (1){
                   scanit = fgetc(undo);
                   if (scanit == '-'){undocur++;}
                   if (undocur == undonumber){break;}
                   if (feof(undo)){break;}

               }


               for (var1 = 0; var1 <= 7; var1++){
                   for (var2 = 0; var2 <= 2; var2++){
                       fscanf(undo,"%d",scanint);
                       deck[var1][var2] = scanint;
                   }
               }
               fprintf(undo,",");
               for (var1 = 0; var1 <= 6; var1++){
                   for (var2 = 0; var2 <= 12; var2++){
                       fscanf(undo,"%d",scanint);
                       top[var1][var2] = scanint;
                   }
               }
               fprintf(undo,",");
               for (var1 = 0; var1 <= 3; var1++){
                   for (var2 = 0; var2 <= 12; var2++){
                       fscanf(undo,"%d",scanint);
                       ace[var1][var2] = scanint;
                   }
               }
               fprintf(undo,",");
               for (var1 = 0; var1 <= 21; var1++){
                       fscanf(undo,"%d",scanint);
                       bottom[var1] = scanint;
               }
               undonumber--;
               pressed = 1;
           }

           if (!key[KEY_Z] || (!key[KEY_RCONTROL] || !key[KEY_LCONTROL])){pressed = 0;}*/



        if (al_key_down(&state, ALLEGRO_KEY_UP)){deckcur++;/*rest(30);*/}
        if (al_key_down(&state, ALLEGRO_KEY_DOWN)){deckcur--;/*rest(30);*/}
        if (deckcur < -1){deckcur = 7;}
        if (deckcur > decktotal){deckcur =-1;}
        times =0;
        for (var1 = 0; var1 <= 2; var1++){
            if (deck[decktotal][var1] == 0){times++;}
            if (times == 3){decktotal--;}
        }




        if (win_conditions() == 1){/*do a wild win screen*/
            fprintf(fp,"1");
            done = 3;

        }


        if (al_key_down(&state, ALLEGRO_KEY_ENTER)){newgame = 1; }
        if (al_key_down(&state, ALLEGRO_KEY_A)){ace[0][12] = 13; ace[1][12] = 26; ace[2][12] = 39; ace[3][12] = 52;}

    }

    return 1;
}


int mouse(){
    int mouse_x, mouse_y;

    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    mouse_x = mouse.x;
    mouse_y = mouse.y;


    
    returnyes = 0;

    // draw card from deck section

    if (mouse_x > startx && mouse_x < startx + 100 && mouse_y > decky && mouse_y < decky + cardsizey && mouse.buttons & 1 && !pressed){
        deckcur++;
        pressed = 1;
//        play_sample(cardflip, 40, 60, 1000, 0);
    }
    if (mouse_x > startx && mouse_x < startx + 100 && mouse_y > decky && mouse_y < decky + cardsizey && mouse.buttons & 2 && !pressed){
        deckcur--;
        pressed = 1;
//        play_sample(cardflip, 40, 60, 1000, 0);
    }
    if (!mouse.buttons){pressed = 0;}



//deck move
    b = -1;
    if (deck[deckcur][0]){b = 0;}
    if (deck[deckcur][1]){b = 1;}
    if (deck[deckcur][2]){b = 2;}
//if (b == -1){return;}

//deck mouse movement
    if (b != -1 && deckcur != -1 && mouse_x > 350 + (b * cardspace) && mouse_x < 450 + (b * cardspace) && mouse_y > decky && mouse_y < decky + cardsizey && mouse.buttons){
        temp2 = 1;
        temp = deck[deckcur][b];
        if(temp > 13){temp -= 13; temp2++;}
        if(temp > 13){temp -= 13; temp2++;}
        if(temp > 13){temp -= 13; temp2++;}
        if(temp > 13){temp -= 13; temp2++;}
        x = mouse_x - 350 - (b * cardspace);
        y = mouse_y - decky;
        cardcur = deck[deckcur][b];
        deck[deckcur][b] = 0;
        while (mouse.buttons){
            al_get_mouse_state(&mouse);
            mouse_x = mouse.x;
            mouse_y = mouse.y;

//            if (key[KEY_D]){dump();}

//            textprintf_ex(screen,font,10,10,makecol(0,0,0),makecol(250,250,250),"%d",b);

            al_set_target_bitmap(cbuffer);
            al_draw_bitmap(buffer,0,0,0);

            al_set_target_bitmap(cbuffer);
            if (cardset == 1) {
                al_draw_bitmap_region(cardbitmap1, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, mouse_x - x, mouse_y - y, 0);
            } else if (cardset == 2) {
                al_draw_bitmap_region(cardbitmap2, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, mouse_x - x, mouse_y - y, 0);
            }

            al_set_target_backbuffer(display);
            al_draw_bitmap(cbuffer, 0, 0, 0);
            al_flip_display();

//            draw_sprite(cbuffer,buffer,0,0);
//            if (cardset == 1){blit(cardbitmap1,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
//            if (cardset == 2){blit(cardbitmap2,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
//            draw_sprite(screen,cbuffer,0,0);
        }


        acecheck = ace_check();
        topcheck = top_check();

        if (acecheck || topcheck){returnyes = 1;}
        if (!acecheck && !topcheck){
            deck[deckcur][b] = cardcur; // put card back
//            play_sample(wrong, 250, 128, 1000, 0);
        }




    }





//top mouse movement

    for (times = 0; times <= 6; times++){
        for (a = 0; a < 12; a++){
            if (!top[times][a]){break;}
        }

        if(mouse_x > startx + (times * 170) && mouse_x < startx + 100 + (times * 170) && mouse_y > topy + (a * cardspace) - cardspace + (botnum[times] * (cardspace - 10)) && mouse_y < topy + (a * cardspace) + cardsizey - cardspace + (botnum[times] * (cardspace - 10)) && mouse.buttons){
            temp2 = 1;
            temp = top[times][a - 1];
            if(temp > 13){temp -= 13; temp2++;}
            if(temp > 13){temp -= 13; temp2++;}
            if(temp > 13){temp -= 13; temp2++;}
            if(temp > 13){temp -= 13; temp2++;}
            x = mouse_x - startx - (times * 170);
            y = mouse_y - topy - (a * cardspace) + cardspace - (botnum[times] * (cardspace - 10));
            cardcur = top[times][a-1];
            top[times][a - 1] = 0;
            while (mouse.buttons){
                al_get_mouse_state(&mouse);
                mouse_x = mouse.x;
                mouse_y = mouse.y;

//                if (key[KEY_D]){dump();}

                al_set_target_bitmap(cbuffer);
                al_draw_bitmap(buffer,0,0,0);

                al_set_target_bitmap(cbuffer);
                if (cardset == 1) {
                    al_draw_bitmap_region(cardbitmap1, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, mouse_x - x, mouse_y - y, 0);
                } else if (cardset == 2) {
                    al_draw_bitmap_region(cardbitmap2, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, mouse_x - x, mouse_y - y, 0);
                }

                al_set_target_backbuffer(display);
                al_draw_bitmap(cbuffer, 0, 0, 0);
                al_flip_display();

//                draw_sprite(cbuffer,buffer,0,0);
//                if (cardset == 1){masked_blit(cardbitmap1,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
//                if (cardset == 2){masked_blit(cardbitmap2,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
//                draw_sprite(screen,cbuffer,0,0);

            }

            i = a;
            acecheck = ace_check();
            topcheck = top_check();


            if (acecheck || topcheck){returnyes = 1;}
            if (!acecheck && !topcheck){
                top[times][i - 1] = cardcur;
//                play_sample(wrong, 250, 128, 1000, 0);
            }


        }

    }




//top mouse movement (its the one that move many cards at once)

    // times == piles
    // var5 == first_empty

    for (times = 0; times <= 6; times++) {
        for (var5 = 0; var5 < 12; var5++) {
            if (!top[times][var5]) { break; }
        }
        if (var5 > 1) { // if there is more than one card in the pile
            for (a = 0; a < var5 - 1; a++) { // for each card in the stack
                if (mouse_x > startx + (times * 170) && mouse_x < startx + 100 + (times * 170) &&
                    mouse_y > topy + (a * cardspace) + (botnum[times] * (cardspace - 10)) &&
                    mouse_y < topy + (a * cardspace) + cardspace + (botnum[times] * (cardspace - 10)) && mouse.buttons) {
                    x = mouse_x - startx - (times * 170);
                    y = mouse_y - topy - (a * cardspace) + cardspace - (botnum[times] * (cardspace - 10));

                    for (var6 = a; var6 < var5; var6++) {
                        temp2 = 1;
                        temp = top[times][var6];
                        if (temp > 13) {
                            temp -= 13;
                            temp2++;
                        }
                        if (temp > 13) {
                            temp -= 13;
                            temp2++;
                        }
                        if (temp > 13) {
                            temp -= 13;
                            temp2++;
                        }
                        if (temp > 13) {
                            temp -= 13;
                            temp2++;
                        }

                        manycardcur[var6][1] = temp;
                        manycardcur[var6][2] = temp2;
                        manycardcur[var6][0] = top[times][var6];
                        top[times][var6] = 0;
                    }
                    while (mouse.buttons) {
                        al_get_mouse_state(&mouse);
                        mouse_x = mouse.x;
                        mouse_y = mouse.y;


//                        if (key[KEY_D]){dump();}

                        al_set_target_bitmap(cbuffer);
                        al_draw_bitmap(buffer, 0, 0, 0);

//                        draw_sprite(cbuffer,buffer,0,0);
                        for (var6 = a; var6 < var5 + a; var6++) {

                            if (cardset == 1) {
                                al_draw_bitmap_region(cardbitmap1, (100 * manycardcur[var6][1]) - 100,
                                                      (cardsizey * manycardcur[var6][2]) - cardsizey, 100, cardsizey,
                                                      mouse_x - x,
                                                      mouse_y - y + (var6 * cardspace) + cardspace - (a * cardspace),
                                                      0);
                            } else if (cardset == 2) {
                                al_draw_bitmap_region(cardbitmap2, (100 * manycardcur[var6][1]) - 100,
                                                      (cardsizey * manycardcur[var6][2]) - cardsizey, 100, cardsizey,
                                                      mouse_x - x,
                                                      mouse_y - y + (var6 * cardspace) + cardspace - (a * cardspace),
                                                      0);
                            }

//                            if (cardset == 1){masked_blit(cardbitmap1,cbuffer,(100 * manycardcur[var6][1]) - 100, (cardsizey * manycardcur[var6][2]) - cardsizey, mouse_x - x, mouse_y - y + (var6 * cardspace) + cardspace - (a * cardspace), 100, cardsizey);}
//                            if (cardset == 2){masked_blit(cardbitmap2,cbuffer,(100 * manycardcur[var6][1]) - 100, (cardsizey * manycardcur[var6][2]) - cardsizey, mouse_x - x, mouse_y - y + (var6 * cardspace) + cardspace - (a * cardspace), 100, cardsizey);}

                        }
                        //textprintf_ex(screen,font,100,100,makecol(0,0,0),makecol(250,250,250),"a = %d",manycardcur[0][0]);
//                        draw_sprite(screen,cbuffer,0,0);
                        al_set_target_backbuffer(display);
                        al_draw_bitmap(cbuffer, 0, 0, 0);
                        al_flip_display();

                    }

                    cardcur = manycardcur[0][0];
                    topcheck = top_check();
                    if (topcheck) {
                        for (var6 = 1; var6 < var5; var6++) {
                            top[var3][var2 + var6] = manycardcur[var6][0];
                        }
                        returnyes = 1;
                    }


                    if (!topcheck) {
                        for (var6 = a; var6 < var5; var6++) {
                            top[times][var6] = manycardcur[var6][0];
                        }
//                        play_sample(wrong, 250, 128, 1000, 0);
                    }

                }

            }

        }

    }
    for (var6 = 0; var6 <= 12; var6++) {
        for (var5 = 0; var5 <= 2; var5++) {
            manycardcur[var6][var5] = 0;
        }
    }


//ace mouse movement

    for (times = 0; times <= 3; times++){
        for (a = 0; a < 12; a++){
            if (!ace[times][a]){break;}
        }
        if(mouse_x > acex + (times * 170) && mouse_x < acex + 100 + (times * 170) && mouse_y > decky && mouse_y < decky + cardsizey && mouse.buttons){
            temp2 = 1;
            temp = ace[times][a - 1];
            if(temp > 13){temp -= 13; temp2++;}
            if(temp > 13){temp -= 13; temp2++;}
            if(temp > 13){temp -= 13; temp2++;}
            if(temp > 13){temp -= 13; temp2++;}
            x = mouse_x - acex - (times * 170);
            y = mouse_y - decky;
            cardcur = ace[times][a-1];
            ace[times][a - 1] = 0;
            while (mouse.buttons){
                al_get_mouse_state(&mouse);
                mouse_x = mouse.x;
                mouse_y = mouse.y;

//                if (key[KEY_D]){dump();}


                al_set_target_bitmap(cbuffer);
                al_draw_bitmap(buffer,0,0,0);

                if (cardset == 1) {
                    al_draw_bitmap_region(cardbitmap1, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, mouse_x - x, mouse_y - y, 0);
                } else if (cardset == 2) {
                    al_draw_bitmap_region(cardbitmap2, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, mouse_x - x, mouse_y - y, 0);
                }

                al_set_target_backbuffer(display);
                al_draw_bitmap(cbuffer, 0, 0, 0);
                al_flip_display();

            }

            i = a;
            topcheck = top_check();


            if (topcheck){returnyes = 1;}
            if (!topcheck){
                ace[times][i - 1] = cardcur;
//                play_sample(wrong, 250, 128, 1000, 0);
            }


        }

    }
    if (returnyes){return 1;}
    else {return 0;}
}

int ace_check(){
    int mouse_x, mouse_y;

    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    mouse_x = mouse.x;
    mouse_y = mouse.y;

    for (var1 = 0; var1 <= 3; var1++){
        if(mouse_x > acex + (var1 * 170) && mouse_x < acex + 100 + (var1 * 170) && mouse_y > decky && mouse_y < decky + cardsizey){
            for (var2 = 0; var2 <= 13; var2++){

                int ace_to_empty = ace[var1][0] == 0 && ((cardcur - 1) % 13) == 0;

                if (!ace[var1][var2] && (ace_to_empty || can_ace_move(cardcur, ace[var1][var2 - 1]))) {
                    ace[var1][var2] = cardcur;
                    cardcur = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int top_check(){
    int mouse_x, mouse_y;

    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    mouse_x = mouse.x;
    mouse_y = mouse.y;

    temp2 = 1;
    temp = cardcur;
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}

    int pile;
    for (pile = 0; pile < 7; pile++){

        int first_empty;
        for (first_empty = 0; first_empty < 13; first_empty++) {
            if (!top[pile][first_empty]){break;}
        }

        int top_cards = first_empty > 0 ? first_empty - 1 : 0;


        int card_x = startx + (pile * 170);
        int card_y = topy + (top_cards * cardspace + botnum[pile] * cardspace_bottom);
        int card_w = 100;
        int card_h = cardsizey;


//        if (mouse_x > startx + (pile * 170) &&
//            mouse_x < startx + 100 + (pile * 170) &&
//            mouse_y > topy + (first_empty * cardspace) - cardspace + (botnum[pile] * cardspace) &&
//            mouse_y < topy + (first_empty * cardspace) + cardsizey - cardspace + (botnum[pile] * cardspace)) {
        if (collides(mouse_x, mouse_y, card_x, card_y, card_w, card_h)) {
            printf("collides! %d top_cards: %d %d at card_y:%d\n", botnum[pile], top_cards, cardspace, card_y);
            for (var2 = 0; var2 <= 13; var2++) {

                int king_to_empty = (cardcur - 1) % 13 == 12 && top[pile][0] == 0;

                if (!top[pile][var2] && (can_move(cardcur, top[pile][var2 - 1]) || king_to_empty)) {
                    printf("Moving card %d to top[%d][%d] at card_y:%d\n", cardcur, pile, var2, card_y);
                    top[pile][var2] = cardcur;
                    cardcur = 0;
                    var3 = pile;
                    var1 = first_empty;
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * Returns whether the x,y position is within the box
 * @param x
 * @param y
 * @param box_x
 * @param box_y
 * @param box_w
 * @param box_h
 * @return bool
 */
int collides(int x, int y, int box_x, int box_y, int box_w, int box_h) {
    return x > box_x && x < box_x + box_w && y > box_y && y < box_y + box_h;
}



void setup(){

    decktotal = 7;
//resets all card slots
    for (var1 = 0; var1 <= 6; var1++){
        for (var2 = 0; var2 <= 13; var2++){
            top[var1][var2] = 0;
        }
    }
    for (var1 = 0; var1 <= 7; var1++){
        for (var2 = 0; var2 <= 2; var2++){
            deck[var1][var2] = 0;
        }
    }
    for (var1 = 0; var1 <= 3; var1++){
        for (var2 = 0; var2 <= 13; var2++){
            ace[var1][var2] = 0;
        }
    }
    for (var2 = 0; var2 <= 21; var2++){
        bottom[var1] = 0;
    }



    for (var1 = 0; var1 <= 52; var1++){
        cards[var1] = var1 + 1;
    }



    for (i = 0; i < 52; i++) {
        j = rand() % 52;
        k = cards[i];
        cards[i] = cards[j];
        cards[j] = k;
    }


    for (var1 = 0; var1 <= 6; var1++){
        top[var1][0] = cards[var1];
    }//sets cards on top

    for (var1 = 0; var1 <= 21; var1++){
        bottom[var1] = cards[var1 + 7];
    }//sets cards on bottom

    var3 = 28;
    for (var1 = 0; var1 <= 7; var1++){
        for (var2 = 0; var2 <= 2; var2++){
            deck[var1][var2] = cards[var3];
            var3++;
        }
    }//sets cards in deck


    newgame = 0;
}




void draw(){
    al_set_target_bitmap(buffer);
    al_draw_bitmap(backround,0,0,0);

    al_set_target_bitmap(buffer);
    al_draw_bitmap(outline,0,0,0);

    for (a = 0; a <= 3; a++){

        for (b = 0; b < 13; b++){
            if (ace[a][b]){find_ace();}
        }
    }//ace slot parser/draw

    y = 24;
    a = deckcur;
    for (b = 0; b < 3; b++){
        if (deck[a][b]){find_deck();}

    }//deck slot parser/draw
    if (deckcur < decktotal){
        al_set_target_bitmap(buffer);
        if (cardset == 1){al_draw_bitmap_region(cardbitmap1, 0, cardsizey * 4, 100, cardsizey, startx, 24, 0);}
        if (cardset == 2){al_draw_bitmap_region(cardbitmap2, 0, cardsizey * 4, 100, cardsizey, startx, 24, 0);}
    }


    // bottom draw

    ALLEGRO_BITMAP * cardbitmap = cardset == 1 ? cardbitmap1 : cardbitmap2;

    find_bottom();
    al_set_target_bitmap(buffer);
    for (int pile = 0; pile < 7; pile++) {
        int botx = startx + pile * 170;

        for (int b = 0; b < botnum[pile]; b++) {
            al_draw_bitmap_region(cardbitmap, 0, cardsizey * 4, 100, cardsizey, botx, topy + cardspace_bottom * b, 0);
        }
    }


    x = 161;
    for (a = 0; a < 7; a++){
        y = 224;
        temp3 = 0;

        for (b = 0; b < 13; b++){
            if (top[a][b]){find_top();}
        }
        x += 170;
    }//top slot parser/draw

    if (done == 1){
        done = 2;
    }

    al_set_target_backbuffer(display);
    al_draw_bitmap(buffer, 0, 0, 0);
    al_flip_display();
}





void find_deck(){
    temp2 = 1;
    temp = deck[a][b];
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}


    if (deckcur != -1){
        al_set_target_bitmap(buffer);
        if (cardset == 1){al_draw_bitmap_region(cardbitmap1, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, 350 + (b * cardspace), y, 0);}
        if (cardset == 2){al_draw_bitmap_region(cardbitmap2, (100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, 350 + (b * cardspace), y, 0);}

    }


}


void find_top(){
    temp2 = 1;
    temp = top[a][b];
    if(a >= 0){temp3 = (botnum[a] * (cardspace - 10));}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}

    al_set_target_bitmap(buffer);

    if (cardset == 1){al_draw_bitmap_region(cardbitmap1,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, x, y + temp3 + (b * cardspace), 0);}
    if (cardset == 2){al_draw_bitmap_region(cardbitmap2,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, 100, cardsizey, x, y + temp3 + (b * cardspace), 0);}
    //textprintf_ex(buffer,font,x,y + temp3,makecol(0,0,0),makecol(250,250,250),"%d",top[a][b]);


}


void find_ace(){
    x = 671;
    y = 24;
    temp2 = 0;
    temp = ace[a][b];
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}
    if(temp > 13){temp -= 13; temp2++;}

    al_set_target_bitmap(buffer);

    if (cardset == 1){al_draw_bitmap_region(cardbitmap1,(100 * temp) - 100, (cardsizey * temp2), 100, cardsizey, x + (170 * a), y, 0);}
    if (cardset == 2){al_draw_bitmap_region(cardbitmap2,(100 * temp) - 100, (cardsizey * temp2), 100, cardsizey, x + (170 * a), y, 0);}
}


/**
 * Calculates the botnum array from the values in bottom
 */
void find_bottom(){

    int pile_bottom_max = -1; // first does not have bottom
    for (int pile = 0; pile < 7; pile++) {
        int num = 0;
        for (int b = pile_bottom_max; b > pile_bottom_max - pile; b--) {
            if (bottom[b] != 0) {
                num++;
            }
        }
        botnum[pile] = num;

        pile_bottom_max += pile + 1; // next pile has more cards in it. increment index by amount of cards
    }
}

/**
 * Returns whether the source card can be moved onto the dest card
 *
 * @param source card
 * @param dest card
 * @return bool
 */
int can_move(int source, int dest){

    //cards are ones based. convert to zero based
    source = source - 1;
    dest = dest - 1;

    int source_suit = source / 13;
    int source_card = source % 13;
    int dest_suit = dest / 13;
    int dest_card = dest % 13;

    int is_source_black = source_suit == 0 || source_suit == 3;
    int is_dest_black = dest_suit == 0 || dest_suit == 3;

    int suits_same_color = is_source_black == is_dest_black;
    int card_lower = source_card + 1 == dest_card;

    return !suits_same_color && card_lower;
}

/**
 * Returns whether the source card can be moved onto the dest card if the dest card is in the aces pile
 *
 * @param source
 * @param dest
 * @return bool
 */
int can_ace_move(int source, int dest){

    //cards are ones based. convert to zero based
    source = source - 1;
    dest = dest - 1;

    int source_suit = source / 13;
    int source_card = source % 13;
    int dest_suit = dest / 13;
    int dest_card = dest % 13;

    int card_higher = source_card - 1 == dest_card;

    return source_suit == dest_suit && card_higher;
}

/**
 * Returns whether the game has been won
 *
 * @return bool
 */
int win_conditions(){
    for (int pile = 0; pile < 4; pile++) {
        if (ace[pile][12] == 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * Flips up a bottom pile card if all the cards on top have been moved away
 * Safe to call multiple times
 */
void flip_bottom(){
    int pile_bottom_max = -1; // first does not have bottom
    for (int pile = 0; pile < 7; pile++) {
        if (top[pile][0] == 0) {
            for (int b = pile_bottom_max; b > pile_bottom_max - pile; b--) {
                if (bottom[b] != 0) {
                    top[pile][0] = bottom[b];
                    bottom[b] = 0;
                    break;
                }
            }
        }
        pile_bottom_max += pile + 1; // next pile has more cards in it. increment index by amount of cards
    }

    // arrangement of bottom[]
    // nothing
    // 0
    // 1  2
    // 3  4  5
    // 6  7  8  9
    // 10 11 12 13 14
    // 15 16 17 18 19 20
}

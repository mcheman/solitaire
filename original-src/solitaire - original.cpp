#include <allegro.h>
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

BITMAP * backround;
BITMAP * buffer;
BITMAP * outline;
BITMAP * cardbitmap1;
BITMAP * cardbitmap2;
BITMAP * cursor;
BITMAP * cbuffer;
BITMAP *bmp_buff;

SAMPLE * wrong;
SAMPLE * cardflip;

FILE *fp;
FILE *dumpfile;



int var1,var2,var3,var4,var5,var6,var7,var8,var9;//meaningless variables use for itterations

int cardspace = 30;

int x,y,a,b;
int botx,boty;
int botnum[6];

int done = 0;
int newgame = 1;

int cardsizey = 145;

int scanint;
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
int bottom[22];
int cards[52];   
int temp;
int temp2;
int temp3;
int cardnumber1 ,cardnumber2;
int suit1 ,suit2;
int manycardcur[13][3];
int lose,win;
int scanit;


int floater;

int finished = 0;
int used;

int cardset = 1;
	int i, j, k;

void setup();
void draw();
void find_deck();
void find_top();
void find_bottom();
void find_ace();
int mouse();
void is_exit();
void highcolor_fade_out(int speed);
int ace_check();
int top_check();
int bot(int tim);
int can_move(int cardstart, int cardfinish);
int can_ace_move(int cardstart, int cardfinish);
int win_conditions();
void dump();
void flip_bottom();
void highcolor_fade_in(BITMAP *bmp_orig, int speed ,int highx, int highy);



int main (void)
{


	allegro_init();
    install_keyboard(); 
	install_mouse();
	install_timer();
	install_sound(DIGI_AUTODETECT,MIDI_NONE,0);
	set_color_depth(32); 
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1440,900,0,0);

    fp = fopen("highscores.txt","r");

    srand(time(NULL));

	bmp_buff = create_bitmap(SCREEN_W, SCREEN_H);
    backround = load_bitmap("backround.tga",NULL);
	outline = load_bitmap("outline.bmp",NULL);
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
	cbuffer = create_bitmap(SCREEN_W,SCREEN_H);
    cardbitmap1 = load_bitmap("cards1.bmp",NULL);
	cardbitmap2 = load_bitmap("cards2.bmp",NULL);
    cursor = load_bitmap("cursor.bmp",NULL);

	wrong = load_sample("wong.wav");
	cardflip = load_sample("cardflip.wav");

set_mouse_sprite(cursor);
show_mouse(screen);

enable_hardware_cursor();
set_close_button_callback(is_exit);

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
       

		if (newgame){setup();}

		//if (key[KEY_1]){set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1440,900,0,0);show_mouse(screen);}
      //  if (key[KEY_2]){set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1680,1050,0,0);show_mouse(screen);}
		if (key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4])){is_exit();}
        

		if (deckcur == -1){
			
		for (var1 = 0; var1 < 8; var1++){
			for (var2 = 0; var2 < 2; var2++){
				if (deck[var1][var2] == 0){deck[var1][var2] = deck[var1][var2+1]; deck[var1][var2+1] = 0;}
			
			}
			if (deck[var1][2] == 0 && var1 != 7){deck[var1][2] = deck[var1+1][0]; deck[var1+1][0] = 0;}
		}
	
		}


		
		flip_bottom();
		

 
		if (key[KEY_D]){dump();}
		if (key[KEY_4]){cardsizey = 155; cardset = 2;}
		if (key[KEY_3]){cardsizey = 145; cardset = 1;}

		if (key[KEY_7]){set_window_title("Allegro rules!");}
		else {set_window_title("solitaire");}


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



		if (key[KEY_UP]){deckcur++;rest(30);}
		if (key[KEY_DOWN]){deckcur--;rest(30);}
		if (deckcur < -1){deckcur = 7;}
		if (deckcur > decktotal){deckcur =-1;}
		times =0;
		for (var1 = 0; var1 <= 2; var1++){
			if (deck[decktotal][var1] == 0){times++;}
			if (times == 3){decktotal--;}
		}




		if (win_conditions() == 1){/*do a wild win screen*/fprintf(fp,"1");done = 3;  highcolor_fade_out(4);
		/*BITMAP * tempbuf = create_bitmap(100,10); 
		textprintf_ex(tempbuf,font,0,0,makecol(250,250,250),-1,"Press Any Key To Play Again");
		highcolor_fade_in(tempbuf, 4,SCREEN_W / 2 - 40, SCREEN_H / 2); destroy_bitmap(tempbuf);*/
        clear_keybuf();
		clear_bitmap(buffer);
			while (!keypressed()){ 	
				if (!win && !lose){floater = 100;}
				if (lose == 1 && win == 0){floater = 0;}
				if (win == 1 && lose == 0){floater = 100;}
				if (win && lose){floater = win * 100 / (win + lose) ;}
				textprintf_ex(buffer,font,SCREEN_W / 2 - 80,SCREEN_H / 2 + 60,makecol(250,250,250),-1,"Press Any Key To Play Again");
				textprintf_ex(buffer,font,SCREEN_W / 2 - 29,SCREEN_H / 2,makecol(250,250,250),-1,"You Have Won");
				textprintf_ex(buffer,font,1285,858,makecol(200,200,200),-1,"Games Won       %d",win);
				textprintf_ex(buffer,font,1285,869,makecol(200,200,200),-1,"Games Lost      %d",lose);
				textprintf_ex(buffer,font,1285,880,makecol(200,200,200),-1,"Win Percentage  %d",floater);
				draw_sprite(screen,buffer,0,0);
			}
			if (!key[KEY_ESC] && done != 1){system("solitaire.exe");}

		}


if (key[KEY_ENTER]){newgame = 1; rest(50); }
if (key[KEY_A]){ace[0][12] = 13; ace[1][12] = 26; ace[2][12] = 39; ace[3][12] = 52;}


rest(20);


	}//while loop end


destroy_bitmap(buffer);
destroy_bitmap(outline);
destroy_bitmap(backround);
destroy_bitmap(cardbitmap1);
destroy_bitmap(cardbitmap2);
destroy_bitmap(cursor);
destroy_bitmap(cbuffer);

destroy_sample(wrong);
destroy_sample(cardflip);


allegro_exit();
fclose(fp);
//fclose(undo);

return 1;
    }//program end
END_OF_MAIN() 
int mouse(){
	returnyes = 0;

	if (mouse_x > startx && mouse_x < startx + 100 && mouse_y > decky && mouse_y < decky + cardsizey && mouse_b & 1 && !pressed){deckcur++; pressed = 1; play_sample(cardflip, 40, 60, 1000, 0);}
	if (mouse_x > startx && mouse_x < startx + 100 && mouse_y > decky && mouse_y < decky + cardsizey && mouse_b & 2 && !pressed){deckcur--; pressed = 1; play_sample(cardflip, 40, 60, 1000, 0);}
	if (!mouse_b){pressed = 0;}



//deck move
b = -1;
if (deck[deckcur][0]){b = 0;}
if (deck[deckcur][1]){b = 1;}
if (deck[deckcur][2]){b = 2;}
//if (b == -1){return;}

//deck mouse movement
	if (b != -1 && deckcur != -1 && mouse_x > 350 + (b * cardspace) && mouse_x < 450 + (b * cardspace) && mouse_y > decky && mouse_y < decky + cardsizey && mouse_b){
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
		while (mouse_b){

		if (key[KEY_D]){dump();}

        textprintf_ex(screen,font,10,10,makecol(0,0,0),makecol(250,250,250),"%d",b);
        draw_sprite(cbuffer,buffer,0,0);
		if (cardset == 1){blit(cardbitmap1,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
		if (cardset == 2){blit(cardbitmap2,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
		draw_sprite(screen,cbuffer,0,0);
		}


acecheck = ace_check();
topcheck = top_check();

if (acecheck || topcheck){returnyes = 1;}
if (!acecheck && !topcheck){deck[deckcur][b] = cardcur; play_sample(wrong, 250, 128, 1000, 0);}




}





//top mouse movement

for (times = 0; times <= 6; times++){
    for (a = 0; a < 12; a++){
		if (!top[times][a]){break;}
	}

	if(mouse_x > startx + (times * 170) && mouse_x < startx + 100 + (times * 170) && mouse_y > topy + (a * cardspace) - cardspace + (bot(times) * (cardspace - 10)) && mouse_y < topy + (a * cardspace) + cardsizey - cardspace + (bot(times) * (cardspace - 10)) && mouse_b){
	    temp2 = 1;
		temp = top[times][a - 1];
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
			x = mouse_x - startx - (times * 170);
			y = mouse_y - topy - (a * cardspace) + cardspace - (bot(times) * (cardspace - 10));
			cardcur = top[times][a-1];
			top[times][a - 1] = 0;
		while (mouse_b){

			if (key[KEY_D]){dump();}

        draw_sprite(cbuffer,buffer,0,0);
		if (cardset == 1){masked_blit(cardbitmap1,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
		if (cardset == 2){masked_blit(cardbitmap2,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
		draw_sprite(screen,cbuffer,0,0);
		
		}

i = a;
acecheck = ace_check();
topcheck = top_check();


if (acecheck || topcheck){returnyes = 1;}
if (!acecheck && !topcheck){top[times][i - 1] = cardcur; play_sample(wrong, 250, 128, 1000, 0);}


	}

}




//top mouse movement (its the one that move many cards at once)

for (times = 0; times <= 6; times++){
    for (var5 = 0; var5 < 12; var5++){
		if (!top[times][var5]){break;}
	}
if (var5 > 1){
  for (a = 0; a < var5 - 1; a++){
	if(mouse_x > startx + (times * 170) && mouse_x < startx + 100 + (times * 170) && mouse_y > topy + (a * cardspace) + (bot(times) * (cardspace - 10)) && mouse_y < topy + (a * cardspace) + cardspace + (bot(times) * (cardspace - 10)) && mouse_b){
	        x = mouse_x - startx - (times * 170);
			y = mouse_y - topy - (a * cardspace) + cardspace - (bot(times) * (cardspace - 10));
		
	  for (var6 = a; var6 < var5; var6++){
		temp2 = 1;
		temp = top[times][var6];
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
						
			manycardcur[var6][1] = temp;
			manycardcur[var6][2] = temp2;
			manycardcur[var6][0] = top[times][var6];
			top[times][var6] = 0;
	  }
		while (mouse_b){


			if (key[KEY_D]){dump();}

        draw_sprite(cbuffer,buffer,0,0);
		for (var6 = a; var6 < var5 + a; var6++){

		if (cardset == 1){masked_blit(cardbitmap1,cbuffer,(100 * manycardcur[var6][1]) - 100, (cardsizey * manycardcur[var6][2]) - cardsizey, mouse_x - x, mouse_y - y + (var6 * cardspace) + cardspace - (a * cardspace), 100, cardsizey);}
		if (cardset == 2){masked_blit(cardbitmap2,cbuffer,(100 * manycardcur[var6][1]) - 100, (cardsizey * manycardcur[var6][2]) - cardsizey, mouse_x - x, mouse_y - y + (var6 * cardspace) + cardspace - (a * cardspace), 100, cardsizey);}
	
	}
		//textprintf_ex(screen,font,100,100,makecol(0,0,0),makecol(250,250,250),"a = %d",manycardcur[0][0]);
		draw_sprite(screen,cbuffer,0,0);
		
		}

cardcur = manycardcur[0][0];
topcheck = top_check();
if (topcheck){
	for (var6 = 1; var6 < var5; var6++){
      top[var3][var2 + var6] = manycardcur[var6][0];
	}
returnyes = 1;
}


if (!topcheck){
	for (var6 = a; var6 < var5; var6++){
      top[times][var6] = manycardcur[var6][0];
	}
play_sample(wrong, 250, 128, 1000, 0);
}

	  }

	}

  } 

}
	for (var6 = 0; var6 <= 12; var6++){
		for (var5 = 0; var5 <= 2; var5++){
			manycardcur[var6][var5] = 0;
		}
	}


//ace mouse movement

for (times = 0; times <= 3; times++){
    for (a = 0; a < 12; a++){
		if (!ace[times][a]){break;}
	}
	if(mouse_x > acex + (times * 170) && mouse_x < acex + 100 + (times * 170) && mouse_y > decky && mouse_y < decky + cardsizey && mouse_b){
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
		while (mouse_b){

			if (key[KEY_D]){dump();}


        draw_sprite(cbuffer,buffer,0,0);
		if (cardset == 1){masked_blit(cardbitmap1,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
		if (cardset == 2){masked_blit(cardbitmap2,cbuffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, mouse_x - x, mouse_y - y, 100, cardsizey);}
		draw_sprite(screen,cbuffer,0,0);
		
		}

i = a;
topcheck = top_check();


if (topcheck){returnyes = 1;}
if (!topcheck){ace[times][i - 1] = cardcur; play_sample(wrong, 250, 128, 1000, 0);}


	}

}
if (returnyes){return 1;}
else {return 0;}
}

int ace_check(){

for (var1 = 0; var1 <= 3; var1++){ 
	if(mouse_x > acex + (var1 * 170) && mouse_x < acex + 100 + (var1 * 170) && mouse_y > decky && mouse_y < decky + cardsizey){
		for (var2 = 0; var2 <= 13; var2++){
           	if (!ace[var1][var2] && can_ace_move(cardcur, ace[var1][var2 - 1])){ace[var1][var2] = cardcur; cardcur = 0; return 1;}
		}
	}
}
return 0;
}

int top_check(){
temp2 = 1;
temp = cardcur;
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}

for (var3 = 0; var3 <= 6; var3++){

	for (var1 = 0; var1 < 13; var1++){
		if (!top[var3][var1]){break;}
	}


    if(mouse_x > startx + (var3 * 170) && mouse_x < startx + 100 + (var3 * 170) && mouse_y > topy + (var1 * cardspace) - cardspace + (bot(var3) * cardspace) && mouse_y < topy + (var1 * cardspace) + cardsizey - cardspace + (bot(var3) * cardspace)){
		for (var2 = 0; var2 <= 13; var2++){
			if (!top[var3][var2] && can_move(cardcur,top[var3][var2-1])){top[var3][var2] = cardcur; cardcur = 0;return 1;}
		}
	}
}
return 0;
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
          cards[var1] = var1 + 1; 	}
		
//
//	for (var1 = 0; var1 < 52; var1++){
//textprintf_ex(screen,font,100,10 * var1,makecol(0,0,0),makecol(250,250,250),"card = %d , %d",cards[var1], var1);
//}
//clear_keybuf();
//	while(!keypressed()){}




	

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
clear_bitmap(buffer);

   blit(backround,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

draw_sprite(buffer,outline,0,0);


//for (var1 = 0; var1 < 7; var1++){
//textprintf_ex(buffer,font,40 * var1,640,makecol(200,255,255),-1,"%d",top[var1][1]);
//}
//
//for (var1 = 0; var1 < 21; var1++){
//textprintf_ex(buffer,font,40 * var1,670,makecol(200,255,255),-1,"%d",bottom[var1]);
//}
//
//for (var1 = 0; var1 < 8; var1++){
//	for (var2 = 0; var2 < 3; var2++){
//textprintf_ex(buffer,font,40 * var1,700 + (var2 * 20),makecol(200,255,255),-1,"%d",deck[var1][var2]);
//	}}





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
			if (cardset == 1){masked_blit(cardbitmap1,buffer, 0, cardsizey * 4, startx, 24, 100, cardsizey);}
		    if (cardset == 2){masked_blit(cardbitmap2,buffer, 0, cardsizey * 4, startx, 24, 100, cardsizey);}
		}





    for (i = 0; i < 6; i++){botnum[i] = 0;}

	for (a = 0; a < 21; a++){

			find_bottom();

	}//bottom slot parser/draw


    x = 161;
	for (a = 0; a < 7; a++){
		y = 224;
		temp3 = 0;
		
		for (b = 0; b < 13; b++){
			if (top[a][b]){find_top();}
		}
	x += 170;
	}//top slot parser/draw

	if (!win && !lose){floater = 100;}
if (lose == 1 && win == 0){floater = 0;}
if (win == 1 && lose == 0){floater = 100;}
if (win && lose){floater = win * 100 / (win + lose) ;}
textprintf_ex(buffer,font,1285,858,makecol(200,200,200),-1,"Games Won       %d",win);
textprintf_ex(buffer,font,1285,869,makecol(200,200,200),-1,"Games Lost      %d",lose);
textprintf_ex(buffer,font,1285,880,makecol(200,200,200),-1,"Win Percentage  %d",floater);


	if (done == 1){highcolor_fade_out(24); done = 2;}
	if (done){rectfill(buffer,0,0,screen->w,screen->h,makecol(0,0,0));}
   blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}




void find_deck(){
temp2 = 1;
temp = deck[a][b];
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}


if (deckcur != -1){
	if (cardset == 1){masked_blit(cardbitmap1,buffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, 350 + (b * cardspace), y, 100, cardsizey);}
	if (cardset == 2){masked_blit(cardbitmap2,buffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, 350 + (b * cardspace), y, 100, cardsizey);}

}

}


void find_top(){
temp2 = 1;
temp = top[a][b];
if(a > 0){temp3 = (botnum[a - 1] * (cardspace - 10));}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}

	if (cardset == 1){masked_blit(cardbitmap1,buffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, x, y + temp3 + (b * cardspace), 100, cardsizey);}
	if (cardset == 2){masked_blit(cardbitmap2,buffer,(100 * temp) - 100, (cardsizey * temp2) - cardsizey, x, y + temp3 + (b * cardspace), 100, cardsizey);}
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

	if (cardset == 1){masked_blit(cardbitmap1,buffer,(100 * temp) - 100, (cardsizey * temp2), x + (170 * a), y, 100, cardsizey);}
	if (cardset == 2){masked_blit(cardbitmap2,buffer,(100 * temp) - 100, (cardsizey * temp2), x + (170 * a), y, 100, cardsizey);}
}


void find_bottom(){
temp2 = 0;
temp = bottom[a];
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}




botx = startx + 170;
boty = 224;

if(a == 0){if(bottom[0]){botnum[0] = 1;}}

if(a == 1){botx += 170; if(bottom[1]){botnum[1]++;}}
if(a == 2){botx += 170; if(bottom[2]){boty += (cardspace - 10); botnum[1]++;}}


if(a == 3){botx += 340; if(bottom[3]){botnum[2]++;}}
if(a == 4){botx += 340; boty += (cardspace - 10); if(bottom[4]){botnum[2]++;}}
if(a == 5){botx += 340; boty += (cardspace - 10) * 2; if(bottom[5]){botnum[2]++;}}

if(a == 6){botx += 510; if(bottom[6]){botnum[3]++;}}
if(a == 7){botx += 510; boty += (cardspace - 10); if(bottom[7]){botnum[3]++;}}
if(a == 8){botx += 510; boty += (cardspace - 10) * 2; if(bottom[8]){botnum[3]++;}}
if(a == 9){botx += 510; boty += (cardspace - 10) * 3; if(bottom[9]){botnum[3]++;}}

if(a == 10){botx += 680; if(bottom[10]){botnum[4]++;}}
if(a == 11){botx += 680; boty += (cardspace - 10); if(bottom[11]){botnum[4]++;}}
if(a == 12){botx += 680; boty += (cardspace - 10) * 2; if(bottom[12]){botnum[4]++;}}
if(a == 13){botx += 680; boty += (cardspace - 10) * 3; if(bottom[13]){botnum[4]++;}}
if(a == 14){botx += 680; boty += (cardspace - 10) * 4; if(bottom[14]){botnum[4]++;}}

if(a == 15){botx += 850; if(bottom[15]){botnum[5]++;}}
if(a == 16){botx += 850; boty += (cardspace - 10); if(bottom[16]){botnum[5]++;}}
if(a == 17){botx += 850; boty += (cardspace - 10) * 2; if(bottom[17]){botnum[5]++;}}
if(a == 18){botx += 850; boty += (cardspace - 10) * 3; if(bottom[18]){botnum[5]++;}}
if(a == 19){botx += 850; boty += (cardspace - 10) * 4; if(bottom[19]){botnum[5]++;}}
if(a == 20){botx += 850; boty += (cardspace - 10) * 5; if(bottom[20]){botnum[5]++;}}


if (bottom[a] != 0){
	if (cardset == 1){masked_blit(cardbitmap1,buffer, 0, cardsizey * 4, botx, boty, 100, cardsizey);}
	if (cardset == 2){masked_blit(cardbitmap2,buffer, 0, cardsizey * 4, botx, boty, 100, cardsizey);}


}
		//textprintf_ex(buffer,font,botx,boty,makecol(0,0,0),makecol(250,250,250),"%d",bottom[a]);

}
int bot(int tim){
	if (tim == 0){return 0;}
	else{
return botnum[tim - 1];
	}
}
void highcolor_fade_out(int speed)
{ 
    
     clear_keybuf();
        
            int a;
                 
            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, buffer, 0, 0);
                vsync();
				if (done == 3){textprintf_ex(bmp_buff,font,SCREEN_W / 2 - 29,SCREEN_H / 2,makecol(250,250,250),-1,"You Have Won");}
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
				if (keypressed()){break;}
            }
            destroy_bitmap(bmp_buff);
        
     

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}

void is_exit(){

fprintf(fp,"0");
done = 1;




}
int can_move(int cardstart, int cardfinish){
suit1 = 1;
cardnumber1 = cardstart;
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}


if (!top[var3][0] && cardnumber1 == 13){return 1;}

suit2 = 1;
cardnumber2 = cardfinish;
if(cardnumber2 > 13){cardnumber2 -= 13; suit2++;}
if(cardnumber2 > 13){cardnumber2 -= 13; suit2++;}
if(cardnumber2 > 13){cardnumber2 -= 13; suit2++;}


if (suit1 == 1 && (suit2 == 2 || suit2 == 3) && cardnumber1 + 1 == cardnumber2){return 1;}

if (suit1 == 2 && (suit2 == 1 || suit2 == 4) && cardnumber1 + 1 == cardnumber2){return 1;}

if (suit1 == 3 && (suit2 == 1 || suit2 == 4) && cardnumber1 + 1 == cardnumber2){return 1;}

if (suit1 == 4 && (suit2 == 2 || suit2 == 3) && cardnumber1 + 1 == cardnumber2){return 1;}


return 0;
}

int can_ace_move(int cardstart, int cardfinish){
suit1 = 1;
cardnumber1 = cardstart;
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if (ace[var1][0] == 0 && cardnumber1 == 1){return 1;}

suit2 = 1;
cardnumber2 = cardfinish;
if(cardnumber2 > 13){cardnumber2 -= 13; suit2++;}
if(cardnumber2 > 13){cardnumber2 -= 13; suit2++;}
if(cardnumber2 > 13){cardnumber2 -= 13; suit2++;}



if (suit1 == suit2 && cardnumber2 + 1 == cardnumber1){return 1;}
return 0;
}
int win_conditions(){
int yeswin = 0;
suit1 = 1;
cardnumber1 = ace[0][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){yeswin++;}	

suit1 = 1;
cardnumber1 = ace[1][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){yeswin++;}

suit1 = 1;
cardnumber1 = ace[2][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){yeswin++;}

suit1 = 1;
cardnumber1 = ace[3][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){yeswin++;}

if (yeswin == 4){return 1;}
else {return 0;}

}



void dump(){

	int itter1,itter2;

dumpfile = fopen("dump.txt","w");
fprintf(dumpfile,"int var1 = %d,var2 = %d,var3 = %d,var4 = %d,var5 = %d,var6 = %d,var7 = %d,var8 = %d,var9 = %d;\n",var1,var2,var3,var4,var5,var6,var7,var8,var9);



fprintf(dumpfile,"int x = %d,y = %d,a = %d,b = %d;\n",x,y,a,b);
fprintf(dumpfile,"int botx = %d,boty = %d;\n",botx,boty);

fprintf(dumpfile,"int botnum[0] = %d , botnum[1] = %d ,botnum[2] = %d ,botnum[3] = %d ,botnum[4] = %d ,botnum[5] = %d\n",botnum[0],botnum[1],botnum[2],botnum[3],botnum[4],botnum[5]);





fprintf(dumpfile,"int done = %d\n",done);
fprintf(dumpfile,"int newgame = %d;\n",newgame);
fprintf(dumpfile,"int times = %d\n",times);
fprintf(dumpfile,"int acecheck = %d, topcheck = %d\n",acecheck,topcheck);
fprintf(dumpfile,"int cardcur = %d\n;",cardcur);
fprintf(dumpfile,"int pressed = %d\n",pressed);


for (itter1 = 0; itter1 <= 7; itter1++){
	for (itter2 = 0; itter2 <= 2; itter2++){
fprintf(dumpfile,"int deck[%d][%d] = %d\n",itter1,itter2,deck[itter1][itter2]);
	}}

fprintf(dumpfile,"int deckcur = %d;\n",deckcur);
fprintf(dumpfile,"int decktotal = %d\n",decktotal);


for (itter1 = 0; itter1 <= 6; itter1++){
	for (itter2 = 0; itter2 <= 12; itter2++){
		fprintf(dumpfile,"int top[%d][%d] = %d\n",itter1,itter2,top[itter1][itter2]);
	}}
for (itter1 = 0; itter1 <= 3; itter1++){
	for (itter2 = 0; itter2 <= 12; itter2++){
fprintf(dumpfile,"int ace[%d][%d] = %d\n",itter1,itter2, ace[itter1][itter2]);
	}}

for (itter1 = 0; itter1 <= 21; itter1++){
fprintf(dumpfile,"int bottom[%d] = %d\n",itter1,bottom[itter1]);
}

for (itter1 = 0; itter1 <= 51; itter1++){
fprintf(dumpfile,"int cards[%d] = %d\n",itter1,cards[itter1]); 
}


fprintf(dumpfile,"int temp =%d\n",temp);
fprintf(dumpfile,"int temp2 =%d\n",temp2);
fprintf(dumpfile,"int temp3 =%d\n",temp3);
fprintf(dumpfile,"int cardnumber1 = %d,cardnumber2 = %d\n",cardnumber1,cardnumber2);
fprintf(dumpfile,"int suit1 = %d,suit2 = %d\n",suit1,suit2);
for (itter1 = 0; itter1 <= 3; itter1++){
	for (itter2 = 0; itter2 <= 12; itter2++){
fprintf(dumpfile,"int manycardcur[%d][%d] = %d\n",itter1,itter2, manycardcur[itter1][itter2]);
	}}
fprintf(dumpfile,"int lose = %d,win = %d\n",lose,win);
fprintf(dumpfile,"int scanit = %d\n",scanit);

fprintf(dumpfile,"int floater = %d\n",floater);

fprintf(dumpfile,"int finished = %d\n",finished);
fprintf(dumpfile,"int used = %d\n",used);

	fprintf(dumpfile,"int i = %d, j = %d, k = %d;\n",i,j,k);
	fprintf(dumpfile,"int cardsizey = %d\n",cardsizey);



fclose(dumpfile);
}

void flip_bottom(){
		//test for fliping bottom cards up
		for (var1 = 0; var1 <= 6; var1++){
			if (!top[var1][0]){
				
				switch (var1){

					case 1:	if (bottom[0]){top[var1][0] = bottom[0]; bottom[0] = 0;play_sample(cardflip, 100, 80, 1000, 0);}
							break;

					case 2:	if (bottom[2]){top[var1][0] = bottom[2]; bottom[2] = 0;play_sample(cardflip, 100, 120, 1000, 0);}
							else if (bottom[1]){top[var1][0] = bottom[1]; bottom[1] = 0;play_sample(cardflip, 100, 120, 1000, 0);}
							break;

					case 3:	if (bottom[5]){top[var1][0] = bottom[5]; bottom[5] = 0;play_sample(cardflip, 100, 128, 1000, 0);}
							else if (bottom[4]){top[var1][0] = bottom[4]; bottom[4] = 0;play_sample(cardflip, 100, 128, 1000, 0);}
							else if (bottom[3]){top[var1][0] = bottom[3]; bottom[3] = 0;play_sample(cardflip, 100, 128, 1000, 0);}
							break;

					case 4:	if (bottom[9]){top[var1][0] = bottom[9]; bottom[9] = 0;play_sample(cardflip, 100, 138, 1000, 0);}
							else if (bottom[8]){top[var1][0] = bottom[8]; bottom[8] = 0;play_sample(cardflip, 100, 138, 1000, 0);}
							else if (bottom[7]){top[var1][0] = bottom[7]; bottom[7] = 0;play_sample(cardflip, 100, 138, 1000, 0);}
							else if (bottom[6]){top[var1][0] = bottom[6]; bottom[6] = 0;play_sample(cardflip, 100, 138, 1000, 0);}
							break;

					case 5:	if (bottom[14]){top[var1][0] = bottom[14]; bottom[14] = 0;play_sample(cardflip, 100, 170, 1000, 0);}
							else if (bottom[13]){top[var1][0] = bottom[13]; bottom[13] = 0;play_sample(cardflip, 100, 170, 1000, 0);}
							else if (bottom[12]){top[var1][0] = bottom[12]; bottom[12] = 0;play_sample(cardflip, 100, 170, 1000, 0);}
							else if (bottom[11]){top[var1][0] = bottom[11]; bottom[11] = 0;play_sample(cardflip, 100, 170, 1000, 0);}
							else if (bottom[10]){top[var1][0] = bottom[10]; bottom[10] = 0;play_sample(cardflip, 100, 170, 1000, 0);}
							break;

					case 6:	if (bottom[20]){top[var1][0] = bottom[20]; bottom[20] = 0;play_sample(cardflip, 100, 210, 1000, 0);}
							else if (bottom[19]){top[var1][0] = bottom[19]; bottom[19] = 0;play_sample(cardflip, 100, 210, 1000, 0);}
							else if (bottom[18]){top[var1][0] = bottom[18]; bottom[18] = 0;play_sample(cardflip, 100, 210, 1000, 0);}
							else if (bottom[17]){top[var1][0] = bottom[17]; bottom[17] = 0;play_sample(cardflip, 100, 210, 1000, 0);}
							else if (bottom[16]){top[var1][0] = bottom[16]; bottom[16] = 0;play_sample(cardflip, 100, 210, 1000, 0);}
							else if (bottom[15]){top[var1][0] = bottom[15]; bottom[15] = 0;play_sample(cardflip, 100, 210, 1000, 0);}
							break;

					default: break;
				}

			}
		}
}
//void highcolor_fade_in(BITMAP *bmp_orig, int speed ,int highx, int highy)
//{
//   BITMAP *bmp_buff;
//
//    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
//    {
//        int a;
//        if (speed <= 0) speed = 16;
//        
//        for (a = 0; a < 256; a+=speed)
//        {
//            clear(bmp_buff);
//            set_trans_blender(0,0,0,a);
//            draw_trans_sprite(bmp_buff, bmp_orig, highx, highy);
//            vsync();
//            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
//        }
//        destroy_bitmap(bmp_buff);
//    } 
//
//    blit(bmp_orig, screen, 0,0, highx,highy, SCREEN_W, SCREEN_H);
//}
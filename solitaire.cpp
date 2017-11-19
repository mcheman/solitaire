#include <allegro.h>
#include <stdio.h>
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
#define startx 100
#define acex 463

BITMAP * backround;
BITMAP * buffer;
BITMAP * outline;
BITMAP * cardbitmap;
BITMAP * cursor;
BITMAP * cbuffer;
BITMAP *bmp_buff;



int var1,var2,var3,var4,var5,var6,var7,var8,var9;//meaningless variables use for itterations




int x,y,a,b;
int botx,boty;
int botnum[6];

int done = 0;
int newgame = 1;



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



int finished = 0;
int used;

	int i, j, k;

void setup();
void draw();
void find_deck();
void find_top();
void find_bottom();
void find_ace();
void mouse();
void is_exit();
void highcolor_fade_out(int speed);
int ace_check();
int top_check();
int bot(int tim);
int can_move(int cardstart, int cardfinish);
int can_ace_move(int cardstart, int cardfinish);
int win_conditions();


int main (void)
{


	allegro_init();
    install_keyboard(); 
	install_mouse();
	install_timer();
	set_color_depth(32); 
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024,768,0,0);
    

    srand(time(NULL));

	bmp_buff = create_bitmap(SCREEN_W, SCREEN_H);
    backround = load_bitmap("backround.tga",NULL);
	outline = load_bitmap("outline.bmp",NULL);
    buffer = create_bitmap(1024,768);
	cbuffer = create_bitmap(1024,768);
    cardbitmap = load_bitmap("cards.bmp",NULL);
    cursor = load_bitmap("cursor.bmp",NULL);

set_mouse_sprite(cursor);
show_mouse(screen);


set_close_button_callback(is_exit);

	while (!done){
       
		if (newgame){setup();}

		if (key[KEY_1]){set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024,768,0,0);}
        if (key[KEY_2]){set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1280,768,0,0);}
		if (key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4])){is_exit();}
        

		if (deckcur == -1){
			
		for (var1 = 0; var1 < 8; var1++){
			for (var2 = 0; var2 < 2; var2++){
				if (deck[var1][var2] == 0){deck[var1][var2] = deck[var1][var2+1]; deck[var1][var2+1] = 0;}
			
			}
			if (deck[var1][2] == 0 && var1 != 7){deck[var1][2] = deck[var1+1][0]; deck[var1+1][0] = 0;}
		}
	
		}


		
			//test for fliping bottom cards up
		for (var1 = 0; var1 <= 6; var1++){
			if (!top[var1][0]){
				
				switch (var1){

					case 1:	if (bottom[0]){top[var1][0] = bottom[0]; bottom[0] = 0;}
							break;

					case 2:	if (bottom[2]){top[var1][0] = bottom[2]; bottom[2] = 0;}
							else if (bottom[1]){top[var1][0] = bottom[1]; bottom[1] = 0;}
							break;

					case 3:	if (bottom[5]){top[var1][0] = bottom[5]; bottom[5] = 0;}
							else if (bottom[4]){top[var1][0] = bottom[4]; bottom[4] = 0;}
							else if (bottom[3]){top[var1][0] = bottom[3]; bottom[3] = 0;}
							break;

					case 4:	if (bottom[9]){top[var1][0] = bottom[9]; bottom[9] = 0;}
							else if (bottom[8]){top[var1][0] = bottom[8]; bottom[8] = 0;}
							else if (bottom[7]){top[var1][0] = bottom[7]; bottom[7] = 0;}
							else if (bottom[6]){top[var1][0] = bottom[6]; bottom[6] = 0;}
							break;

					case 5:	if (bottom[14]){top[var1][0] = bottom[14]; bottom[14] = 0;}
							else if (bottom[13]){top[var1][0] = bottom[13]; bottom[13] = 0;}
							else if (bottom[12]){top[var1][0] = bottom[12]; bottom[12] = 0;}
							else if (bottom[11]){top[var1][0] = bottom[11]; bottom[11] = 0;}
							else if (bottom[10]){top[var1][0] = bottom[10]; bottom[10] = 0;}
							break;

					case 6:	if (bottom[20]){top[var1][0] = bottom[20]; bottom[20] = 0;}
							else if (bottom[19]){top[var1][0] = bottom[19]; bottom[19] = 0;}
							else if (bottom[18]){top[var1][0] = bottom[18]; bottom[18] = 0;}
							else if (bottom[17]){top[var1][0] = bottom[17]; bottom[17] = 0;}
							else if (bottom[16]){top[var1][0] = bottom[16]; bottom[16] = 0;}
							else if (bottom[15]){top[var1][0] = bottom[15]; bottom[15] = 0;}
							break;

					default: break;
				}

			}
		}
	
		


		if (key[KEY_7]){set_window_title("Allegro rules!");}
		else {set_window_title("solitaire");}


        draw();
        mouse();

		//for (var1 = 0; var1 <= 3; var1++){
		//textprintf_ex(screen,font,100 + (var1 * 100),200,makecol(0,0,0),makecol(250,250,250),"%d",ace[var1][0]);
		//}


		//textprintf_ex(screen,font,10,10,makecol(0,0,0),makecol(250,250,250),"%d",deckcur);


		if (key[KEY_UP]){deckcur++;rest(30);}
		if (key[KEY_DOWN]){deckcur--;rest(30);}
		if (deckcur < -1){deckcur = 7;}
		if (deckcur > decktotal){deckcur =-1;}
		times =0;
		for (var1 = 0; var1 <= 2; var1++){
			if (deck[decktotal][var1] == 0){times++;}
			if (times == 3){decktotal--;}
		}




		if (win_conditions() == 1){/*do a wild win screen*/ is_exit();}


if (key[KEY_ENTER]){newgame = 1; }
if (key[KEY_A]){ace[0][12] = 13; ace[1][12] = 26; ace[2][12] = 39; ace[3][12] = 52;}


rest(20);





	}//while loop end


destroy_bitmap(buffer);
destroy_bitmap(outline);
destroy_bitmap(backround);
destroy_bitmap(cardbitmap);
destroy_bitmap(cursor);
destroy_bitmap(cbuffer);


allegro_exit();

return 1;
    }//program end
END_OF_MAIN() 
void mouse(){

	if (mouse_x > startx && mouse_x < startx + 100 && mouse_y > decky && mouse_y < decky + 145 && mouse_b & 1 && !pressed){deckcur++; pressed = 1;}
	if (mouse_x > startx && mouse_x < startx + 100 && mouse_y > decky && mouse_y < decky + 145 && mouse_b & 2 && !pressed){deckcur--; pressed = 1;}
	if (!mouse_b){pressed = 0;}



//deck move
b = -1;
if (deck[deckcur][0]){b = 0;}
if (deck[deckcur][1]){b = 1;}
if (deck[deckcur][2]){b = 2;}
if (b == -1){return;}

//deck mouse movement
	if (deckcur != -1 && mouse_x > 250 + (b * 20) && mouse_x < 350 + (b * 20) && mouse_y > decky && mouse_y < decky + 145 && mouse_b){
		temp2 = 1;
		temp = deck[deckcur][b];
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
			x = mouse_x - 250 - (b * 20);
			y = mouse_y - decky;
			cardcur = deck[deckcur][b];
			deck[deckcur][b] = 0;
		while (mouse_b){


        textprintf_ex(screen,font,10,10,makecol(0,0,0),makecol(250,250,250),"%d",b);
        draw_sprite(cbuffer,buffer,0,0);
		blit(cardbitmap,cbuffer,(100 * temp) - 100, (145 * temp2) - 145, mouse_x - x, mouse_y - y, 100, 145);
		draw_sprite(screen,cbuffer,0,0);
		}


acecheck = ace_check();
topcheck = top_check();


if (!acecheck && !topcheck){deck[deckcur][b] = cardcur;}




}





//top mouse movement

for (times = 0; times <= 6; times++){
    for (a = 0; a < 12; a++){
		if (!top[times][a]){break;}
	}

	if(mouse_x > startx + (times * 121) && mouse_x < startx + 100 + (times * 121) && mouse_y > topy + (a * 20) - 20 + (bot(times) * 20) && mouse_y < topy + (a * 20) + 145 - 20 + (bot(times) * 20) && mouse_b){
	    temp2 = 1;
		temp = top[times][a - 1];
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
			x = mouse_x - startx - (times * 121);
			y = mouse_y - topy - (a * 20) + 20 - (bot(times) * 20);
			cardcur = top[times][a-1];
			top[times][a - 1] = 0;
		while (mouse_b){



        draw_sprite(cbuffer,buffer,0,0);
		masked_blit(cardbitmap,cbuffer,(100 * temp) - 100, (145 * temp2) - 145, mouse_x - x, mouse_y - y, 100, 145);
		draw_sprite(screen,cbuffer,0,0);
		
		}

i = a;
acecheck = ace_check();
topcheck = top_check();



if (!acecheck && !topcheck){top[times][i - 1] = cardcur;}


	}

}




//top mouse movement (its the one that move many cards at once)

for (times = 0; times <= 6; times++){
    for (var5 = 0; var5 < 12; var5++){
		if (!top[times][var5]){break;}
	}
if (var5 > 1){
  for (a = 0; a < var5 - 1; a++){
	if(mouse_x > startx + (times * 121) && mouse_x < startx + 100 + (times * 121) && mouse_y > topy + (a * 20) + (bot(times) * 20) && mouse_y < topy + (a * 20) + 20 + (bot(times) * 20) && mouse_b){
	        x = mouse_x - startx - (times * 121);
			y = mouse_y - topy - (a * 20) + 20 - (bot(times) * 20);
		
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



        draw_sprite(cbuffer,buffer,0,0);
		for (var6 = a; var6 < var5 + a; var6++){
		masked_blit(cardbitmap,cbuffer,(100 * manycardcur[var6][1]) - 100, (145 * manycardcur[var6][2]) - 145, mouse_x - x, mouse_y - y + (var6 * 20) + 20 - (a * 20), 100, 145);
		}
		textprintf_ex(screen,font,100,100,makecol(0,0,0),makecol(250,250,250),"a = %d",manycardcur[0][0]);
		draw_sprite(screen,cbuffer,0,0);
		
		}

cardcur = manycardcur[0][0];
topcheck = top_check();
if (topcheck){
	for (var6 = 1; var6 < var5; var6++){
      top[var3][var2 + var6] = manycardcur[var6][0];
	}
}


if (!topcheck){
	for (var6 = a; var6 < var5; var6++){
      top[times][var6] = manycardcur[var6][0];
	}

}

	  }

	}

  } 

}



//ace mouse movement

for (times = 0; times <= 3; times++){
    for (a = 0; a < 12; a++){
		if (!ace[times][a]){break;}
	}
	if(mouse_x > acex + (times * 121) && mouse_x < acex + 100 + (times * 121) && mouse_y > decky && mouse_y < decky + 145 && mouse_b){
	    temp2 = 1;
		temp = ace[times][a - 1];
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
		if(temp > 13){temp -= 13; temp2++;}
			x = mouse_x - acex - (times * 121);
			y = mouse_y - decky;
			cardcur = ace[times][a-1];
			ace[times][a - 1] = 0;
		while (mouse_b){



        draw_sprite(cbuffer,buffer,0,0);
		masked_blit(cardbitmap,cbuffer,(100 * temp) - 100, (145 * temp2) - 145, mouse_x - x, mouse_y - y, 100, 145);
		draw_sprite(screen,cbuffer,0,0);
		
		}

i = a;
topcheck = top_check();



if (!topcheck){ace[times][i - 1] = cardcur;}


	}

}

}

int ace_check(){

for (var1 = 0; var1 <= 3; var1++){ 
	if(mouse_x > acex + (var1 * 121) && mouse_x < acex + 100 + (var1 * 121) && mouse_y > decky && mouse_y < decky + 145){
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


    if(mouse_x > startx + (var3 * 121) && mouse_x < startx + 100 + (var3 * 121) && mouse_y > topy + (var1 * 20) - 20 + (bot(var3) * 20) && mouse_y < topy + (var1 * 20) + 145 - 20 + (bot(var3) * 20)){
		for (var2 = 0; var2 <= 13; var2++){
			if (!top[var3][var2] && can_move(cardcur,top[var3][var2-1])){top[var3][var2] = cardcur; cardcur = 0;return 1;}
		}
	}
}
return 0;
}




void setup(){

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


	for (var1 = 0; var1 < 7; var1++){
     top[var1][0] = cards[var1];
	}//sets cards on top

	for (var1 = 0; var1 < 21; var1++){
     bottom[var1] = cards[var1 + 7];
	}//sets cards on bottom

    var3 = 29;
    for (var1 = 0; var1 < 8; var1++){
		  for (var2 = 0; var2 < 3; var2++){
     deck[var1][var2] = cards[var3];
	 var3++;
		  }
	}//sets cards in deck
		


newgame = 0;
}







void draw(){
clear_bitmap(buffer);

   blit(backround,buffer,0,0,0,0,1024,768);

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
		if (deckcur < decktotal){masked_blit(cardbitmap,buffer, 0, 580, 100, 24, 100, 145);}





    for (i = 0; i < 6; i++){botnum[i] = 0;}

	for (a = 0; a < 21; a++){

			find_bottom();

	}//bottom slot parser/draw


    x = 100;
	for (a = 0; a < 7; a++){
		y = 224;
		temp3 = 0;
		
		for (b = 0; b < 13; b++){
			if (top[a][b]){find_top();}
		}
	x += 121;
	}//top slot parser/draw







	if (done == 1){highcolor_fade_out(24); done = 2;}
	if (done){rectfill(buffer,0,0,screen->w,screen->h,makecol(0,0,0));}
   blit(buffer,screen,0,0,0,0,1024,768);
}





void find_deck(){
temp2 = 1;
temp = deck[a][b];
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}


if (deckcur != -1){masked_blit(cardbitmap,buffer,(100 * temp) - 100, (145 * temp2) - 145, 250 + (b * 20), y, 100, 145);}

}


void find_top(){
temp2 = 1;
temp = top[a][b];
if(a > 0){temp3 = (botnum[a - 1] * 20);}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}

	masked_blit(cardbitmap,buffer,(100 * temp) - 100, (145 * temp2) - 145, x, y + temp3 + (b * 20), 100, 145);
	textprintf_ex(buffer,font,x,y + temp3,makecol(0,0,0),makecol(250,250,250),"%d",top[a][b]);
	
	
}


void find_ace(){
x = 463;
y = 24;
temp2 = 0;
temp = ace[a][b];
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}

	masked_blit(cardbitmap,buffer,(100 * temp) - 100, (145 * temp2), x + (121 * a), y, 100, 145);
}


void find_bottom(){
temp2 = 0;
temp = bottom[a];
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}
if(temp > 13){temp -= 13; temp2++;}




botx = 221;
boty = 224;

if(a == 0){if(bottom[0]){botnum[0] = 1;}}

if(a == 1){botx += 121; if(bottom[1]){botnum[1]++;}}
if(a == 2){botx += 121; if(bottom[2]){boty += 20; botnum[1]++;}}


if(a == 3){botx += 242; if(bottom[3]){botnum[2]++;}}
if(a == 4){botx += 242; boty += 20; if(bottom[4]){botnum[2]++;}}
if(a == 5){botx += 242; boty += 40; if(bottom[5]){botnum[2]++;}}

if(a == 6){botx += 363; if(bottom[6]){botnum[3]++;}}
if(a == 7){botx += 363; boty += 20; if(bottom[7]){botnum[3]++;}}
if(a == 8){botx += 363; boty += 40; if(bottom[8]){botnum[3]++;}}
if(a == 9){botx += 363; boty += 60; if(bottom[9]){botnum[3]++;}}

if(a == 10){botx += 484; if(bottom[10]){botnum[4]++;}}
if(a == 11){botx += 484; boty += 20; if(bottom[11]){botnum[4]++;}}
if(a == 12){botx += 484; boty += 40; if(bottom[12]){botnum[4]++;}}
if(a == 13){botx += 484; boty += 60; if(bottom[13]){botnum[4]++;}}
if(a == 14){botx += 484; boty += 80; if(bottom[14]){botnum[4]++;}}

if(a == 15){botx += 605; if(bottom[15]){botnum[5]++;}}
if(a == 16){botx += 605; boty += 20; if(bottom[16]){botnum[5]++;}}
if(a == 17){botx += 605; boty += 40; if(bottom[17]){botnum[5]++;}}
if(a == 18){botx += 605; boty += 60; if(bottom[18]){botnum[5]++;}}
if(a == 19){botx += 605; boty += 80; if(bottom[19]){botnum[5]++;}}
if(a == 20){botx += 605; boty += 100; if(bottom[20]){botnum[5]++;}}


if (bottom[a] != 0){masked_blit(cardbitmap,buffer, 0, 580, botx, boty, 100, 145);}
		textprintf_ex(buffer,font,botx,boty,makecol(0,0,0),makecol(250,250,250),"%d",bottom[a]);

}
int bot(int tim){
	if (tim == 0){return 0;}
	else{
return botnum[tim - 1];
	}
}
void highcolor_fade_out(int speed)
{ 
    
     
        
            int a;
                 
            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, buffer, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        
     

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}

void is_exit(){

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
int win = 0;
suit1 = 1;
cardnumber1 = ace[0][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){win++;}	

suit1 = 1;
cardnumber1 = ace[1][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){win++;}

suit1 = 1;
cardnumber1 = ace[2][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){win++;}

suit1 = 1;
cardnumber1 = ace[3][12];
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}
if(cardnumber1 > 13){cardnumber1 -= 13; suit1++;}

if(cardnumber1 == 13){win++;}

if (win == 4){return 1;}
else {return 0;}

}


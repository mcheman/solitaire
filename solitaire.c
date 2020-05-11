#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//1 | 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13 clubs
//14|15|16|17|18|19|20|21|22|23|24|25|26 diamonds
//27|28|29|30|31|32|33|34|35|36|37|38|39 hearts
//40|41|42|43|44|45|46|47|48|49|50|51|52 spades
//
//a | 2| 3| 4| 5| 6| 7| 8| 9|10| j| q| k

#define TOP_Y 224
#define DECK_Y 24
#define START_X 161
#define ACE_X 671

#define DECK_SIZE 24

ALLEGRO_BITMAP * backround;
ALLEGRO_BITMAP * buffer;
ALLEGRO_BITMAP * outline;
ALLEGRO_BITMAP * cardbitmap1;
ALLEGRO_BITMAP * cardbitmap2;

ALLEGRO_DISPLAY * display;
ALLEGRO_KEYBOARD_STATE state;
ALLEGRO_EVENT_QUEUE * event_queue;

//SAMPLE * wrong;
//SAMPLE * cardflip;

//FILE *fp;

int var3;

int cardspace = 30;
int cardspace_bottom = 20;

int x,y,a,b;
int botnum[7];

int cardsizey = 145;

int undocur;
int undonumber = 0;
int acecheck, topcheck;
int cardcur;
int pressed = 0;
int deck[DECK_SIZE];
int deckcur = -1;
int decktotal = 8;
int deck_hand_size = 3;
int top[7][13];
int ace[4][13];
int bottom[22]; // only first 20 are actually used
int cards[52];
int temp3;
int lose,win;
int scanit;

int cardset = 1;

int drag_cards[13];
int drag_size = 0;
int *drag_original;
int offset_x = 0;
int offset_y = 0;

void setup_new_game_deck();
void draw();
void find_bottom();
void mouse();
int try_move_to_ace_row(int card);
int try_move_to_top_row(int card);
int can_move(int source, int dest);
int can_ace_move(int source, int dest);
int win_conditions();
void flip_bottom();
int collides(int x, int y, int box_x, int box_y, int box_w, int box_h);
void draw_card(int card, int x, int y);

void next_deck_hand(int is_forward);
void compact_deck();

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

//    fp = fopen("highscores.txt","r");

    srand(time(NULL));
//    srand(26);

    backround = al_load_bitmap("backround.bmp");
    outline = al_load_bitmap("outline.bmp");
    buffer = al_create_bitmap(SCREEN_W, SCREEN_H);
    cardbitmap1 = al_load_bitmap("cards1.bmp");
    cardbitmap2 = al_load_bitmap("cards22.bmp");

    al_convert_mask_to_alpha(outline, al_map_rgb(255, 0, 255));
    al_convert_mask_to_alpha(cardbitmap1, al_map_rgb(255, 0, 255));
    al_convert_mask_to_alpha(cardbitmap2, al_map_rgb(255, 0, 255));

//    wrong = load_sample("wong.wav");
//    cardflip = load_sample("cardflip.wav");


    al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

//    while (1){
//        scanit = fgetc(fp);
//        if (feof(fp)){break;}
//        if (scanit == '0'){lose++;}
//        if (scanit == '1'){win++;}
//    }

//    remove("undo.txt");
//    fclose(fp);
//    fp = fopen("highscores.txt","a");
//FILE *undo = fopen("undo.txt","w+");
//fprintf(undo,"-");
//undonumber = 1;

    setup_new_game_deck();

    while (1){
        al_get_keyboard_state(&state);

        ALLEGRO_EVENT event;
        while (!al_is_event_queue_empty(event_queue)) {
            al_get_next_event(event_queue, &event);

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                return 0;
            }
        }

        //if (key[KEY_1]){set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1440,900,0,0);show_mouse(screen);}
        //  if (key[KEY_2]){set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1680,1050,0,0);show_mouse(screen);}

        if (al_key_down(&state, ALLEGRO_KEY_2)){cardsizey = 155; cardset = 2;}
        if (al_key_down(&state, ALLEGRO_KEY_3)){cardsizey = 145; cardset = 1;}

//        if (key[KEY_7]){set_window_title("Allegro rules!");}
//        else {set_window_title("solitaire");}

        flip_bottom();

        draw();
        al_set_target_backbuffer(display);
        al_draw_bitmap(buffer, 0, 0, 0);
        al_flip_display();

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

        if (al_key_down(&state, ALLEGRO_KEY_UP)){next_deck_hand(1);/*rest(30);*/}
        if (al_key_down(&state, ALLEGRO_KEY_DOWN)){next_deck_hand(0);/*rest(30);*/}

        if (win_conditions() == 1){/*do a wild win screen*/
//            fprintf(fp,"1");
            break;
        }

        if (al_key_down(&state, ALLEGRO_KEY_ENTER)){
            setup_new_game_deck();
        }
        if (al_key_down(&state, ALLEGRO_KEY_A)){ace[0][12] = 13; ace[1][12] = 26; ace[2][12] = 39; ace[3][12] = 52;}

    }

    return 1;
}


void mouse(){
    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);

    // draw card from deck section
    if (mouse.x > START_X && mouse.x < START_X + 100 && mouse.y > DECK_Y && mouse.y < DECK_Y + cardsizey && mouse.buttons & 1 && !pressed){
        next_deck_hand(1);
        pressed = 1;
//        play_sample(cardflip, 40, 60, 1000, 0);
    }
    if (mouse.x > START_X && mouse.x < START_X + 100 && mouse.y > DECK_Y && mouse.y < DECK_Y + cardsizey && mouse.buttons & 2 && !pressed){
        next_deck_hand(0);
        pressed = 1;
//        play_sample(cardflip, 40, 60, 1000, 0);
    }
    if (!mouse.buttons){pressed = 0;}

    //deck move
    int deck_index = -1;
    b = -1;
    for (int c = 0; c < deck_hand_size; c++) {
        int card_index = deckcur * deck_hand_size + c;
        if (deck[card_index]) {
            deck_index = card_index;
            b = c;
            break;
        }
    }

    //if (b == -1){return;}

    int deck_moved = 0;
    int ace_moved = 0;

    int previous_index = 0;
    int previous_pile = 0;

    // check if we want to start moving a card

    //deck mouse movement
    if (drag_size == 0 && b != -1 && deckcur != -1 && collides(mouse.x, mouse.y, 350 + ((deck_hand_size - b) * cardspace), DECK_Y, 100, cardsizey)) {
        offset_x = 350 + ((deck_hand_size - b) * cardspace) - mouse.x;
        offset_y = DECK_Y - mouse.y;
        cardcur = deck[deck_index];
        deck[deck_index] = 0;
        deck_moved = 1;
        previous_index = deck_index;
    }

    //ace mouse movement
    for (int piles = 0; piles <= 3; piles++) {
        for (a = 0; a < 12; a++) {
            if (!ace[piles][a]) { break; }
        }
        if (drag_size == 0 && collides(mouse.x, mouse.y, ACE_X + (piles * 170), DECK_Y, 100, cardsizey)) {
            offset_x = ACE_X + (piles * 170) - mouse.x;
            offset_y = DECK_Y - mouse.y;
            cardcur = ace[piles][a - 1];
            ace[piles][a - 1] = 0;
            ace_moved = 1;
            previous_index = a - 1;
            previous_pile = piles;
        }
    }

    int any_moved = deck_moved || ace_moved;

    // If we've clicked on a card, move it around
    while (mouse.buttons && any_moved) {
        al_get_mouse_state(&mouse);

        draw();

        draw_card(cardcur, mouse.x + offset_x, mouse.y + offset_y);

        al_set_target_backbuffer(display);
        al_draw_bitmap(buffer, 0, 0, 0);
        al_flip_display();
    }

    // if anything was moved, put it in its place
    if (any_moved) {
        acecheck = try_move_to_ace_row(cardcur);
        topcheck = try_move_to_top_row(cardcur);

        if (acecheck || topcheck) { cardcur = 0; }

        // we didn't move it anywhere, put card back
        if (!acecheck && !topcheck) {
            if (deck_moved) {
                deck[previous_index] = cardcur;
            } else if (ace_moved) {
                ace[previous_pile][previous_index] = cardcur;
            }
            // play_sample(wrong, 250, 128, 1000, 0);
        }
    }

    if (drag_size > 0 && !mouse.buttons) {
        if (drag_size == 1) {
            acecheck = try_move_to_ace_row(drag_cards[0]);
            if (acecheck) {
                drag_size = 0;
                return;
            }
        }

        topcheck = try_move_to_top_row(drag_cards[0]);
        // move rest of cards
        if (topcheck) {
            drag_original = top[var3];
        } else {
//                        play_sample(wrong, 250, 128, 1000, 0);
        }

        int first_empty = 0;
        for (; first_empty < 13; first_empty++) {
            if (drag_original[first_empty] == 0) {
                break;
            }
        }

        if (topcheck) {
            first_empty--; // card was already inserted before running empty check. decrement so it's the same as the other case
        }

        for (int i = 0; i < drag_size; i++) {
            drag_original[first_empty + i] = drag_cards[i];
        }

        drag_size = 0;
    }

    // don't continue since we're already dragging something. We don't want to rerun the drag code
    if (drag_size) {
        return;
    }

    // If we're not clicking then there's nothing to drag
    if (!mouse.buttons) {
        return;
    }

    //top mouse movement (its the one that move many cards at once)
    for (int pile = 0; pile < 7; pile++) {
        int max = 13;
        for (int c = 13; c >= 0; c--) {
            if (top[pile][c] == 0) {
                max = c;
                continue; // card doesn't exist here
            }

            int card_x = START_X + (pile * 170);
            int bottom_card_offset = botnum[pile] * (cardspace - 10);
            int card_y = TOP_Y + bottom_card_offset + c * cardspace;

            if (collides(mouse.x, mouse.y, card_x, card_y, 100, cardsizey)) {
                // move cards to drag state
                drag_size = max - c;
                for (int i = 0; i < drag_size; i++) {
                    drag_cards[i] = top[pile][c + i];
                    top[pile][c + i] = 0;
                }

                // get offsets for mouse drawing
                offset_x = card_x - mouse.x;
                offset_y = card_y - mouse.y;

                drag_original = top[pile];
                break;
            }
        }
    }
}

/**
 * Draw the next deck hand
 * @param is_forward 1 to advance the deck, 0 to go back one
 */
void next_deck_hand(int is_forward) {
    deckcur += is_forward ? 1 : -1;

    if (deckcur >= decktotal || deckcur < 0) {
        deckcur = -1;
        compact_deck();
    }
}

/**
 * Compresses space so the cards in the deck array are contiguous
 * @return The total number of cards left in the deck
 */
void compact_deck() {
    int num_cards = 0;

    for (int i = 0; i < DECK_SIZE; i++) {
        if (deck[i] == 0) { // no card present

            // find next non empty card
            int j = i + 1;
            for (; j < DECK_SIZE; j++) {
                if (deck[j] != 0) { // card we need to move forward in array
                    break;
                }
            }

            if (j < DECK_SIZE && deck[j] != 0) { // if there's a card present, we move it over the current empty element
                deck[i] = deck[j];
                deck[j] = 0;
            }
        }

        if (deck[i] != 0) {
            num_cards++;
        }
    }

    num_cards += deck_hand_size - 1; // we add this to make sure it rounds up
    decktotal = num_cards / deck_hand_size;
}


/**
 * @param card Currently selected card
 * @return True if card was moved
 */
int try_move_to_ace_row(int card){
    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    int isAce = ((card - 1) % 13) == 0;

    for (int i = 0; i <= 3; i++){
        if (collides(mouse.x, mouse.y, ACE_X + (i * 170), DECK_Y, 100, cardsizey)) {
            // find first free space
            int first_empty = 0;
            for (; first_empty < 13; first_empty++) {
                if (ace[i][first_empty] == 0) {
                    break;
                }
            }

            // do we want to place ace card in ace slot?
            int ace_to_empty = isAce && ace[i][0] == 0;

            if (ace_to_empty || can_ace_move(card, ace[i][first_empty - 1])) {
                ace[i][first_empty] = card;
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @param card  Currently selected card
 * @return True if card was moved
 */
int try_move_to_top_row(int card){
    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    int isKing = (card - 1) % 13 == 12;

    int pile;
    for (pile = 0; pile < 7; pile++){
        int first_empty = 0;
        for (; first_empty < 13; first_empty++) {
            if (top[pile][first_empty] == 0) {
                break;
            }
        }

        // this is the topmost card
        int top_cards = first_empty > 0 ? first_empty - 1 : 0;


        int card_x = START_X + (pile * 170);
        int card_y = TOP_Y + (top_cards * cardspace + botnum[pile] * cardspace_bottom);
        int card_w = 100;
        int card_h = cardsizey;

        if (collides(mouse.x, mouse.y, card_x, card_y, card_w, card_h)) {
            printf("collides! %d top_cards: %d %d at card_y:%d\n", botnum[pile], top_cards, cardspace, card_y);
            for (int j = 0; j <= 13; j++) {

                // do we want to place king card in top slot?
                int king_to_empty = isKing && top[pile][0] == 0;

                if (!top[pile][j] && (can_move(card, top[pile][j - 1]) || king_to_empty)) {
                    printf("Moving card %d to top[%d][%d] at card_y:%d\n", cardcur, pile, j, card_y);
                    top[pile][j] = card;
                    var3 = pile;
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

/**
 * Shuffles deck and deals cards
 */
void setup_new_game_deck() {
    decktotal = 8;
    //resets all card slots
    memset(top, 0, sizeof(top));
    memset(deck, 0, sizeof(deck));
    memset(ace, 0, sizeof(ace));
    memset(bottom, 0, sizeof(bottom));

    // create cards in sorted order
    for (int i = 0; i < 52; i++){
        cards[i] = i + 1;
    }

    // fisher-yates shuffle
    int shuffled_cards[52];

    for (int i = 51; i >= 0; i--) {
        int random_card = rand() % (i + 1); // rand mod remaining cards to select

        // pick random card
        shuffled_cards[i] = cards[random_card];

        // replace picked card with the last card in the array so the unpicked cards are at the beginning
        cards[random_card] = cards[i];
    }

    // deal cards
    int card_index = 0;

    for (int i = 0; i < 7; i++){
        top[i][0] = shuffled_cards[card_index++];
    }

    for (int i = 0; i < 21; i++){
        bottom[i] = shuffled_cards[card_index++];
    }

    for (int i = 0; i < 24; i++){
        deck[i] = shuffled_cards[card_index++];
    }

    assert(card_index == 52);
}

void draw(){
    al_set_target_bitmap(buffer);
    al_draw_bitmap(backround,0,0,0);
    al_draw_bitmap(outline,0,0,0);

    // draw ace slots
    for (int pile = 0; pile < 4; pile++){
        for (int c = 12; c >= 0; c--){
            if (ace[pile][c]){
                draw_card(ace[pile][c], ACE_X + (170 * (pile)), DECK_Y);
                break;
            }
        }
    }

    // render 3 deck cards
    // deckcur is what the current page of the deck is exposed
    if (deckcur != -1) { // deckcur -1 means first page which does not have dealt cards
        for (int c = deck_hand_size - 1; c >= 0; c--) {
            int card = deck[deckcur * deck_hand_size + c];
            if (card) {
                draw_card(card, 350 + ((deck_hand_size - c) * cardspace), DECK_Y);
            }
        }
    }

    if (deckcur < decktotal - 1){
        if (cardset == 1){al_draw_bitmap_region(cardbitmap1, 0, cardsizey * 4, 100, cardsizey, START_X, 24, 0);}
        if (cardset == 2){al_draw_bitmap_region(cardbitmap2, 0, cardsizey * 4, 100, cardsizey, START_X, 24, 0);}
    }


    // bottom draw

    ALLEGRO_BITMAP * cardbitmap = cardset == 1 ? cardbitmap1 : cardbitmap2;

    find_bottom();
    for (int pile = 0; pile < 7; pile++) {
        int botx = START_X + pile * 170;

        for (int b = 0; b < botnum[pile]; b++) {
            al_draw_bitmap_region(cardbitmap, 0, cardsizey * 4, 100, cardsizey, botx, TOP_Y + cardspace_bottom * b, 0);
        }
    }

    x = 0;
    for (int pile = 0; pile < 7; pile++){
        temp3 = 0;

        for (int c = 0; c < 13; c++){
            if (top[pile][c]){
                if(pile >= 0) {
                    temp3 = (botnum[pile] * (cardspace - 10));
                }
                draw_card(top[pile][c], START_X + x, TOP_Y + temp3 + (c * cardspace));
            }
        }
        x += 170;
    }//top slot parser/draw

    // draw cards being dragged
    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    for (int i = 0; i < drag_size; i++) {
        draw_card(drag_cards[i], mouse.x + offset_x, mouse.y + offset_y + (i * cardspace));
    }
}

/**
 * Draws card at x, y location
 *
 * @param card 1 - 53 card index
 * @param x
 * @param y
 */
void draw_card(int card, int x, int y) {
    assert(card > 0);
    assert(card < 53);

    card = card - 1; // convert to zero based

    int suit = card / 13;
    int rank = card % 13;

    // todo switch bitmap at global level
    al_draw_bitmap_region(cardbitmap1, 100 * rank, cardsizey * suit, 100, cardsizey, x, y, 0);
}


/**
 * Calculates the botnum array from the values in bottom
 * botnum is the number of face down cards per pile
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
    if (drag_size > 0) {
        return;
    }

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

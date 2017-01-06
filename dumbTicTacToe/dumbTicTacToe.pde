
int COLS = 3;
int ROWS = 3;

int SCREEN_W = 600;
int SCREEN_H = 600;

int MARK_X = 1;
int MARK_O = -1;

int row_h, col_w;

int human_first;
int win_status;
boolean x_turn;
int[] board;

void setup() {
	size(SCREEN_W, SCREEN_H);	

	row_h = SCREEN_H / ROWS;
	col_w = SCREEN_W / COLS;
	x_turn = true;
	human_first = -1;
	board = new int[9];
	for(int i=0; i < ROWS*COLS; i++){
		board[i] = 0;
	}
}

void draw() {
		drawBoard();
		win_status = checkWin();	
	if( win_status == -2){
		textSize(24);
		text("The game is a draw", 50, 25);
	}else if(win_status == MARK_X ){
		textSize(24);
		text("X's won!", 50, 25);
	}else if(win_status == MARK_O ){
		textSize(24);
		text("O's won!", 50, 25);
	} else{
		if( human_first == -1){
			promptStart();
		} else {
			// computer makes move
			if( (human_first == 0 && x_turn) 
					|| (human_first == 1 && !x_turn) ){
					makeMove(x_turn ? MARK_X : MARK_O);
					x_turn = !x_turn;
				}
			}
		} 
}
void mouseClicked(){
	if( human_first == -1){
		checkPrompt();
	} else {
		if( (human_first == 1 && x_turn) 
				|| (human_first == 0 && !x_turn) ){
			board[ readMouse() ] = x_turn ? MARK_X : MARK_O;
			x_turn = !x_turn;
		}
	} 
}

void drawBoard() {
	background(255,245,220);
	stroke(200, 100, 25);
	strokeWeight( 8);
	for(int i = 1; i < ROWS; i++) {
		line( 0, i * row_h, SCREEN_W, i * row_h);
	}
	for( int j = 1; j < COLS; j++) {
		line( j * col_w, 0, j * col_w, SCREEN_H);

	}
	for( int i = 0; i < ROWS*COLS; i++) {
		drawMark(i, board[i]);
	}
}

void promptStart() {
	textSize(14);
	fill(100,25,200);
	text("Who will make",50,50);
	text("the first move?",50,65);
	text("(Click One)", 50, 80);
	fill(255);
	rect(col_w, 0, 2*col_w, row_h);
	fill(100,25,200);
	text("HUMAN", col_w + 50, 50);
	fill(200);
	rect(2*col_w, 0, 3*col_w, row_h);
	fill(100,25,200);
	text("COMPUTER", 2*col_w + 50, 50);
}
void checkPrompt() {
			if( mouseX > col_w && mouseX < 2*col_w && mouseY<row_h){
				human_first = 1;
			} else if ( mouseX > 2*col_w && mouseY < row_h){
				human_first = 0;
	}
}

void drawMark(int i, int mark) {
	int x = i%3 *  col_w;
	//hopefully will work with Pjs
	int y = floor(i/3) * row_h;

	if(mark == MARK_X ){
		fill(200,40,40);
		textSize(row_h - 10);
		text("X", x + col_w/6, y + row_h - 10);
	} else if(mark == MARK_O) {
		fill(100,75,40);
		textSize(row_h - 10);
		text("O", x + col_w/6, y + row_h - 10);
	}
}

int checkWin() {
	int win = 0;
	//check horizontal/vertical lines
	for(int i=0; i<3; i++){
		//horizontal lines
		if( board[i*3] == board[(i*3)+1]
				&& board[(i*3)+1] == board[(i*3)+2]
				&& board[i*3] != 0)
			win = board[i*3];
		//vertical lines
		if( board[i] == board[i+3]
				&& board[i+3] == board[i+6]
				&& board[i] != 0)
			win = board[i];
	}
	if(win == 0){
		//check diagonals
		if( board[0] == board[4]
				&& board[4] == board[8]
				&& board[0] != 0)
			win = board[0];
		else if( board[2] == board[4]
				&& board[4] == board[6]
				&& board[2] != 0)
			win = board[2];
	}
	if(win == 0){
		//check draw
		boolean draw = true;
		for(int i = 0; i < ROWS*COLS; i++){
			if(board[i] == 0)
				draw = false;
		}
		if(draw)
			win = -2;
	}

	return win;
}

int readMouse() {
	int x = floor(mouseX / col_w);
	int y = floor(mouseY / row_h);

	return (3 * y) + x;
}
void makeMove(int mark) {
	boolean done = false;
	for(int i=0; i < COLS*ROWS; i++){
		if( board[i] == 0 && !done){
			board[i] = 0 - mark;
			// if a move in this sqare by the other player
			// would produce a win for the other player
			if(checkWin() == 0 - mark){
				board[i] = mark;
				done = true;
			}else
				board[i] = 0;
		}
	}
	if( !done ){
		int pos = 0;
		while(pos != -1){
			pos = int(random(0,8));
			if(board[pos] == 0){
				board[pos] = mark;
				pos = -1;
			}
		}
	}
}



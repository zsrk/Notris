#ifndef NOTRIS_GAME_FUNCTIONS_H
#define NOTRIS_GAME_FUNCTIONS_H

struct notrisPiece* notris_create_piece( enum notrisPieceShape pieceShape, struct notrisInfo* npfiInfo ) ;

void notris_move_piece( HANDLE* phInputBuffer, struct notrisInfo* npfiInfo, struct notrisPiece* piece ) ;

void notris_rotate_piece_clockwise( struct notrisPiece* piece ) ;

void notris_setup( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* npfiInfo ) ;

void play_notris( HANDLE* hScreenBufferOne, HANDLE* hScreenBufferTwo, HANDLE* hInputBuffer, 
                  CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* npfiInfo ) ;

#endif /* NOTRIS_GAME_FUNCTIONS_H */
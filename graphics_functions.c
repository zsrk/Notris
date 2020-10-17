#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"
#include "game_entities.h"

void draw_notris_piece( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, notrisPiece* piece )
{
  /*
   * Unsure which method is better. draw_rectangle() initialises and declares a few variables and creates a malloc'd array, which it later has to
   * free. It has to populate this array too. It eventually calls WriteConsoleOutputA() to copy array into Screen Buffer. I think that writing the
   * characters and attributes directly to the console with the API is probably faster, using pairs of WriteConsoleOutputAttribute/Character, as
   * there's only 4 of them.
   */

  /*
    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockOne.X, piece->blockOne.Y, piece->blockOne.X + 1, piece->blockOne.Y + 1 ) ;

    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockTwo.X, piece->blockTwo.Y, piece->blockTwo.X + 1, piece->blockTwo.Y + 1) ;

    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockThree.X, piece->blockThree.Y, piece->blockThree.X + 1, piece->blockThree.Y + 1 ) ;

    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockFour.X, piece->blockFour.Y, piece->blockFour.X + 1, piece->blockFour.Y + 1 ) ;
  */

  CHAR symbol = piece->pieceLook.Char.AsciiChar ;
  WORD attributes = piece->pieceLook.Attributes ;

  DWORD charsWritten = 0 ;
  DWORD attributesWritten = 0 ;

  WriteConsoleOutputAttribute( *phScreenBuffer, &attributes, 1, piece->blockOne, &attributesWritten ) ;
  WriteConsoleOutputCharacter( *phScreenBuffer, &symbol, 1, piece->blockOne, &charsWritten ) ;

  WriteConsoleOutputAttribute( *phScreenBuffer, &attributes, 1, piece->blockTwo, &attributesWritten ) ;
  WriteConsoleOutputCharacter( *phScreenBuffer, &symbol, 1, piece->blockTwo, &charsWritten ) ;

  WriteConsoleOutputAttribute( *phScreenBuffer, &attributes, 1, piece->blockThree, &attributesWritten ) ;
  WriteConsoleOutputCharacter( *phScreenBuffer, &symbol, 1, piece->blockThree, &charsWritten ) ;

  WriteConsoleOutputAttribute( *phScreenBuffer, &attributes, 1, piece->blockFour, &attributesWritten ) ;
  WriteConsoleOutputCharacter( *phScreenBuffer, &symbol, 1, piece->blockFour, &charsWritten ) ;
}


void draw_notris_play_field( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPlayFieldInfo* npfiInfo )
{
  
}

// endX and endY must be at least 1 unit greater than startX and endX respectively.
void draw_rectangle( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, 
                    CHAR asciiValue, WORD asciiAttributes, 
                    SHORT startX, SHORT startY, SHORT endX, SHORT endY )
{
    SHORT bufferWidth = endX ;
    SHORT bufferHeight = endY ;

    COORD characterPosition = { startX, startY } ;
    COORD characterBufferSize = { bufferWidth, bufferHeight } ;
    SMALL_RECT consoleWriteArea = { startX, startY, bufferWidth - 1, bufferHeight - 1 } ;

    // Note that it's a one-dimensional array.
    CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferHeight ) * sizeof( CHAR_INFO ) ) ;

    if( consoleBuffer == NULL )
    {
      report_error( "Failed: CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferWidth ) * sizeof( CHAR_INFO ) )" ) ;
    }

    // Accessed like a matrix by using offset. bufferWidth * y gives the first cell of each row, and column given by adding x to it.
    for (int y = 0; y < bufferHeight; ++y)
    {
      for (int x = 0; x < bufferWidth; ++x)
      {
        consoleBuffer[ x + bufferWidth * y ].Char.AsciiChar = asciiValue ;
        consoleBuffer[ x + bufferWidth * y ].Attributes = asciiAttributes ;
      }
    }

    if( !WriteConsoleOutputA( *phScreenBuffer, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea ) )
    {
      report_error( "WriteConsoleOutputA( *phScreenBuffer, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea )" ) ;
    }

    free( consoleBuffer ) ;
}

void erase_notris_piece( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPiece* piece )
{
  CHAR formerChar = piece->pieceLook.Char.AsciiChar ;
  CHAR formerAttribute = piece->pieceLook.Attributes ;

  piece->pieceLook.Char.AsciiChar = ' ' ;
  piece->pieceLook.Attributes = 0 ;

  draw_notris_piece( phScreenBuffer, csbiInfo, piece ) ;

  piece->pieceLook.Char.AsciiChar = formerChar ;
  piece->pieceLook.Attributes = formerAttribute ;
}
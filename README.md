# Ex7-8 - Chess project

Link to ex7-8 google drive folder: <a href="https://drive.google.com/drive/u/0/folders/1mh6nYhWWGg0QrrsFxb4m5Bho-vIqf2Uo/" target="_blank">Ex7-8 Google Drive</a>

This is the mid project for the 'Advanced Programming' course.
In this exercise you will design and implement a chess game.
By doing that, you will use a lot of the knowledge and skills you aquired throughout the first 6 weeks of the course.
Make sure to also do bonus :)

### Ex7-8Files
Contains base files for Ex7-8

### .gitlab-ci.yml
Pipeline file for auto-tests

### Bonus (11)
1) En Passant

En passant is a special pawn capture where a pawn can capture an opponent's pawn
that has just moved two squares forward from its starting position,
landing right beside it, as if the opponent's pawn had only moved one square.

2) Castling

Castling is a special move that simultaneously moves the king two squares towards a rook
and places the rook on the square the king crossed,
getting the king to safety and developing the rook

3) Pawn Promotion

Promotion happens when a pawn makes it all the way to the end of the board,
when the pawn gets there, he is automatically promoted into a queen.

4) GUI integration

All of the special moves listed above are not supported by the default GUI
We integrated our Bonuses into the frontend by upgrading the protocol, making the GUI listen to us.

5) Dark mode in GUI

The GUI's default color palette is using white only, which is not very user friendly.
Therefore we added an optional button that makes the GUI's color palette in dark mode, 
so it is easier to play chess at night.

6) GUI message's Box changes

We have changed some of the GUI's messages that appear in the message box
to be more user friendly, as well as added our protocol improvements into the messages options

7) Checkmate

Checkmate is when the king is placed in check and has no legal moves to escape.
When a checkmate happens, the game ends immediately, and the player who did the checkmate wins

8) Stalemate

Stalemate is one of the drawing rules of chess.
It happens when the player who has to move has no legal moves available
The game then ends immediately in a tie.

9) Draw by insufficient material

insufficient material is when the game ends in a draw because the remaining pieces on the board
aren't enough for either player to force a checkmate.

10) The fifty move rule

The fifty move rule says that if no pawn has moved and no piece has been captured
in the last fifty moves by each player (100 half moves total) the game will end in a draw.

11) Three-fold repetition

Three-fold repetition happens if the exact same board position (pieces, moves available, castling, en passant)
occurs three times, with the same player to move each time, signaling no real progress
if that happens, the game will end in a draw.
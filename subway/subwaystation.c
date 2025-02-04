#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define MAX_LINE_LENGTH 1024
#define MAX_TRACK_LINES 128

typedef int bool;

typedef struct HashNode {
  char *key;
  int value;
  struct HashNode *next;
} HashNode;

char track_map[MAX_TRACK_LINES][MAX_LINE_LENGTH];
const char *filename = "track.txt";
char current_line[MAX_LINE_LENGTH];
int current_index = 1;
int max_read_line = 0;
int running_ok = 1;
int redraw_track = 0;

char *read_line_from_file(const char *filename, int line_number, char *buffer) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  };

  int current_line = 1;
  while (fgets(buffer, MAX_LINE_LENGTH, file)) {
    if (current_line == line_number) {
      fclose(file);
      return buffer;
    };
      
    current_line++;
  };

  fclose(file);
  return NULL;
}

bool change_line() {
  if (read_line_from_file(filename, current_index, current_line) == NULL) {
    return FALSE;
  };

  current_index++;
  return TRUE;
}

void clear_track(){
   memset(&track_map, 0, MAX_TRACK_LINES*MAX_LINE_LENGTH);
}

int read_from_file_set_track() {
  FILE *file_to_read;
  char line_read[MAX_LINE_LENGTH];
  int current_map_line = 0;

  if ( (file_to_read = fopen(filename, "r")) == NULL ) return -1;

  clear_track();
  while ( fgets(line_read, MAX_LINE_LENGTH, file_to_read) ){
    if (current_map_line >= MAX_TRACK_LINES)
      return -2;
    
    strcpy(track_map[current_map_line], line_read);
    // printf("%s", track_map[current_map_line]);
    current_map_line++;
  }
  max_read_line = current_map_line;

  fclose(file_to_read);

  return 0;
}

void print_track() {
  int current_line=0;
  
#ifdef LINUX
  system("clear");
#else
  system("cls");
#endif

  for ( ; current_line < max_read_line; current_line++ ) {
    printf("%s", track_map[current_line]);
  };
  printf("\n");
}

void move_ahead(char ahead_piece, char train_type, int train_size) {
  switch (ahead_piece) {
    case '-':
      break;
    
    case '+':
      break;
    
    case '|':
      break;
    
    case '/':
      break;
    
    case '\\':
      break;
    
    case 'S':
      break;
    
    case 'B':
      break;
    
    case 'b':
      break;

    case 'A':
      break;

    case 'a':
      break;

    default:
      break;
  };
}

void move_left(char motor_char, int motor_pos) {
  // printf("indo para a esquerda\n");
  // printf("peça à frente: %c\n", current_line[motor_pos + 1]);

  char front_piece = current_line[motor_pos + 1];
}

void move_right(char motor_char, int motor_pos) {
  // printf("indo para a direita\n");
  // printf("peça à frente: %c\n", current_line[motor_pos - 1]);

  char front_piece = current_line[motor_pos - 1];
}

bool has_engine(char *line, int linesize) {
  char *line_pointer
  int i = 0;

  for (line_pointer = line; i < linesize; i++) {

    if ( *line_pointer > 65 && *line_pointer < 90 ) {
      setup_engine_position(*line_pointer);
    };
    
    line_pointer++;
  };

  if (strchr(line, )) {
    return TRUE; 
  };

  return FALSE;
}

void search_trains() {
  int current_line;
  int linelen;
  for ( current_line = 0; current_line < max_read_line; current_line++ ) {
    linelen = strlen(track_map[current_line]);
    if (has_engine( track_map[current_line], linelen)) {
      
    };
  };
}

void move_trains() {
  while (TRUE) {
    int current_line_length = strlen(current_line);

    if (!change_line()) break;

    for (int c = 0; c < current_line_length; c++) {
      if (current_line[c] == 'A' || current_line[c] == 'B') {        
        // Achou um Motor!
        printf("%s\n", current_line); // print do trem

        char motor_char = current_line[c]; 

        if ( c > 0 && current_line[c - 1] != tolower(motor_char)) {
          // Ele esta indo para a direita!
          // printf("letra a esquerda: %c\n", current_line[c - 1]);
          printf("indo para a esquerda!\n");

          move_right(motor_char, c); // Move à direita
        }

        else {
          // Ele esta indo para a esquerda!
          // printf("letra a direita: %c\n", current_line[c + 1]);
          printf("indo para a direita!\n");

          move_left(motor_char, c); // Move à esquerda!
        };
      };
    };

    change_line();
  };
}

int main() {
  // int line_number = 5;
  // char line[MAX_LINE_LENGTH];
  // change_line();
  // move_trains();
  if ( read_from_file_set_track() < 0 ) {
    return -1;
  };

  print_track();

  while ( running_ok ){

    // reconhecer trens
    search_trains();
    // reconhecer sentido dos movimentos
    setup_train_movement();
    // checar estacoes e casos especiais
    search_stations();
        //search_crossings();
    // mover trens
    move_trains();

    // check_colisions();

    if ( redraw_track )
      print_track();

  }

  return 0;
}
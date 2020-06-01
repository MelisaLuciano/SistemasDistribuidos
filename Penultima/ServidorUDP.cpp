#include "Respuesta.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>  

using namespace std;
void reverse(char* begin, char* end);

void reverseWords(char* s) 
{ 
    char* word_begin = s; 
    char* temp = s; /* temp is for word boundry */
  
    /*STEP 1 of the above algorithm */
    while (*temp) { 
        temp++; 
        if (*temp == '\0') { 
            reverse(word_begin, temp - 1); 
        } 
        else if (*temp == ' ') { 
            reverse(word_begin, temp - 1); 
            word_begin = temp + 1; 
        } 
    } /* End of while */
  
    /*STEP 2 of the above algorithm */
    reverse(s, temp - 1); 
} 

void reverse(char* begin, char* end) 
{ 
    char temp; 
    while (begin < end) { 
        temp = *begin; 
        *begin++ = *end; 
        *end-- = temp; 
    } 
} 

int main(int argc, char const *argv[])
{   
    int puertoServer;
    string cadena;

    cout << "Puerto: " << endl;
    cin >> puertoServer;
    Respuesta respuesta(puertoServer);

    while(1)
    { 
        mensaje *m = respuesta.getRequest();

        char cadenota[4000];
        strcpy(cadenota, m->arguments);
        
        printf("%s", m->arguments);
        
        reverseWords(cadenota); 
        printf("%s", cadenota);

        respuesta.sendReply(cadenota, m->IP, m->puerto);
    }
    return 0;
}
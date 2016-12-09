//James Neverson 10193581
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int running = 0;
int position[5];

int winner() {
	for ( int i = 0; i < 5; i++ ) {
		if ( position[i] >= 40 ) {
			return (i+1);
		}
	}
	return (0);
}

void* enter_listener( void *args ) {
	char* buff;
	printf("Welcom to CISC220 Racing Arena\nHit Enter to move forward\n");
	scanf("%s", buff);
	position[0]++;
	running = 1;
	while ( running ) {
		scanf("%s", buff);
		position[0]++;
		if ( winner() ) {
			pthread_exit( NULL );
		}
		printf("%d",position[0]);
	}
}

void* ai_executer( void *tid ) {	
	int ai_id = (int) tid;
	while (1) {
		while ( running ) {
			printf("sup");
			position[ ai_id ]++;
			usleep( rand() % 10000 );
			if ( winner() ) {
				pthread_exit( NULL );
			}
		}
	}
}

void* update( void *args ) {
	int won;
	while (1) {
		while ( running ) {
			system("clear");
			for ( int i = 0; i < 5; i++ ) {
				for ( int ii = 0; ii < position[i]; ii++ ) {
					printf("~");
				}
				printf("|->");
				for ( int ii = 0; ii < ( 40 - position[i] ); ii++ ) {
					printf(" ");
				}
				printf("# Lane %d #\n", i );
			}
			won = winner();
			if ( won ) {
				if ( won == 1 ) {
					printf("You WIN!");
				}
				else {
					printf("Player %d WINS", won );
				}
				pthread_exit( NULL );
			}
			usleep( 200 );
		}
	}
}

int main() {
	pthread_t threads[6];
	pthread_create( threads, NULL, enter_listener, NULL );
	for ( int i = 1; i < 5; i++ ) {
		pthread_create( threads + i, NULL, ai_executer, (void*) i );
	}
	pthread_create( threads + 5, NULL, update, NULL);
	for ( int i = 0; i< 5; i++ ) {
		pthread_join( threads[i], NULL);	
	}
	pthread_exit(NULL);
	return (0);
}

// By: Abdullah Aljahdali
// CMPS 3350
// lab12.cpp
//
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4

enum note_t {
	C = 1,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B,
	END = B+1,
	HALF_STEPS_PER_OCTAVE = B
};

double freq(note_t note, int octave_delta);


int main(int argc, char *argv[])
{
	note_t note;
	int octave_delta;

	if (argc > 4) {
		cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA> [TOLERANCE]" << endl;
		return 0;
	}

	note = (note_t)(toupper(argv[1][0]) - 64);
	switch(toupper(argv[1][0])) {
		case 'A': note = A; break;
		case 'B': note = B; break;
		case 'C': note = C; break;
		case 'D': note = D; break;
		case 'E': note = E; break;
		case 'F': note = F; break;
		case 'Z':

		double tolerance = atof(argv[3]);
		if (atoi(argv[2]) != 0) {
			cout << "Try: " << argv[0] << " Z 0 " << tolerance << endl;
		} else {
			int badElementCount = 0;

			printf("+note octave value    diff\n");
			printf("----- ------ -------- ------------+\n");

			for(int i=C-1; i<END; i+=1) {
				for(int j=C; j<END; j+=1) {

					double value = freq((note_t)j, i);
					double diff = abs(value - (roundf(value * 100) / 100));

					int flag = diff<tolerance;
					if (flag) { badElementCount++; }

					// comment the following if statemnt to print all freq
					if (i<C || (j<F && i<Cs))
						printf("%3d %5d %10.6g  %10.6g %10s\n", \
						 				  j,  i, value, diff, (flag)?("  good"):("<------ bad"));

					// comment the following if statemnt to calculate all bad elements
					if (badElementCount>20) { goto result; }
				}
			}

			result:
			printf("...\n");
			printf("...\n");
			printf("...\n");
			printf("bad element count: %d\n", badElementCount);
			printf("unit test complete.\n");
		}

		return 0;
	}
	//You may call your unit test here...

	if (note > END) {
		cout << "Invalid note!" << endl;
		return 1;
	}
	octave_delta = atoi(argv[2]);
	cout << HALF_STEPS_PER_OCTAVE << endl;
	cout << freq(note, octave_delta) << endl;
	return 0;
}

//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
	double freq;
	double factor;
	double a;
	int n;
	int octave = octave_delta - F0_octave;

	a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
	n = note - F0_note;
	freq = F0 * pow(a, (double)n);
	factor = pow(2.0, (double)octave);
	freq = freq * factor;
	return freq;
}

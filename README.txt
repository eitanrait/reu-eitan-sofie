README
is_verbose: -V
    prints extra information

add_noise: -n <float noise_offset>
    optional to add noise of signal [-offset, offset]

random seed: -R <int seed>
    default seed 0
    for PRNG

output_file_csv: -o <output file name.csv>
    no quotes
    enter output file name (.csv)
    default is output.csv

output_file_tst: -f <output file name.txt>
    no quotes
    default is entropy_output.txt
    created in detection.c

boat U: -u "<i coordinate> <j coordinate> <u_activity>"
    u_activities: randomwalk, up, down, diagonal

boat V: -v "<i coordinate> <j coordinate> <v_activity>"
    v_activity: chasing, following, randomwalk

time: -t <int maxsteps>
    default: 600

detection: -d <detect>
    detect activities: chasing, randomwalk

chasing probability: -c <float chasing_prob>
    give probability [0, 1.0] that chasing algo will take bresenham's next best move


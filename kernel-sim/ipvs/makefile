
ipvs:ipvs_wrr.o ipvs_sched.o  ipvs_ctl.o main.o
	gcc -g -o $@ $^

ipvs_wrr.o: ipvs_wrr.c
	gcc -g -c  $<
	gcc -g -c ipvs_wrr.c

ipvs_sched.o: ipvs_sched.c
	gcc -g -c  $<
	gcc -g -c ipvs_sched.c

ipvs_ctl.o: ipvs_ctl.c
	gcc -g -c  $<
	gcc -g -c ipvs_ctl.c

main.o: main.c
	gcc -g -c  $<
	gcc -g -c main.c


clean:
	rm -rf *.o
	rm ipvs

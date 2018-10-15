CC = gcc
LD = gcc
CFLAGS = -c
LDFLAGS =  -O3 -o

OBJS =  modelagem2D.o parametros.o modeling_data.o  readFile.o update_wave_field.o wave_equation.o writeToFile.o apply_Reynolds_Boundary.o ad_borda_model_vel.o  apply_Cerjan_Boundary.o calc_coef_damping_zones.o geometria.o ricker_wavelet.o

MODELAGEM2D = modelagem2D

EXECS=$(MODELAGEM2D)

.c.o:
	$(CC) $(CFLAGS) $<

all:$(EXECS)

modelagem2D:$(OBJS)
	$(CC) $(LDFLAGS) $@ $^ -lm
clean:
	rm -f *.o $(EXECS)

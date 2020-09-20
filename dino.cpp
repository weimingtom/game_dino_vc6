// dino.cpp : Defines the entry point for the console application.
//

//see https://github.com/makerdiary/nrf52840-m2-devkit/blob/master/examples/python/dino/dino.py
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "Board.h"
#include "DigitalIO.h"
#include "DisplayIO.h"
#include "AdafruitImageload.h"

#define DEBUG_TEST 0
//to adjust fps, search FRAME_SLEEP

unsigned char os_urandom(int count, int index) 
{
	//see srand(time(NULL));
	if (count == 1 && index == 0)
	{
		return rand() & 0xff;
	}
	else
	{
#if !defined(_MSC_VER)
		while(1);
#else
		throw; exit(1);
#endif
	}
}

void time_sleep(double second) 
{
	if (MainFrameGetMsg() != 0) 
	{
		exit(0);
		return;
	}
	Sleep((long)(second * 1000));
}

void update_score(TileGrid *score, int points) 
{
	printf("update_score: %d\n", points);
    score->set(2, points % 10);
    score->set(1, (points / 10) % 10);
    score->set(0, (points / 100) % 10);
}

void test1(Display *display, Group *group)
{
	while (true) 
	{
		display->show(group);
	}
}

int main()
{
	DigitalIO *button = DigitalIO::DigitalInOut(Board::USR_BTN);
	button->direction = INPUT;
	button->pull = UP;

	Display *display = Board::DISPLAY;

	Group *group = new Group(8);

	//Load bitmap
	Palette *palette = NULL;
	Palette *palette2 = NULL;
	AdafruitImageload *ground_bmp = AdafruitImageload::load("/img/ground512x12.bmp",
		DisplayIO::Bitmap,
		DisplayIO::Palette, &palette);

	palette->make_transparent(1);
	palette->set(0, 0x808000);

	TileGrid *ground = new TileGrid(ground_bmp, palette,
                            120,
                            1,
                            2,
                            12,
                            0,
                            192);

	for (int x = 0; x < 120; ++x) {
		ground->set(x, x);
	}

	group->append(ground);

	AdafruitImageload *dinosaur_bmp = AdafruitImageload::load("/img/dinosaur132x47.bmp",
		DisplayIO::Bitmap,
		DisplayIO::Palette, &palette);

	palette->make_transparent(1);
	palette->set(0, 0x404040);

	// 44x47
	TileGrid *dinosaur = new TileGrid(dinosaur_bmp, palette,
								  1,
								  1,
								  44,
								  47,
								  0,
								  0,
								  2);
	dinosaur->set_x(8);
	dinosaur->set_y(160);

	group->append(dinosaur);

	AdafruitImageload *cactus_bmp = AdafruitImageload::load("/img/cactus15x32.bmp",
		DisplayIO::Bitmap,
		DisplayIO::Palette, &palette);
	palette->make_transparent(1);
	palette->set(0, 0x008000);

	TileGrid *cactus = new TileGrid(cactus_bmp, palette);
	cactus->set_x(240);
	cactus->set_y(170);
	group->append(cactus);

	AdafruitImageload *cactus2_bmp = AdafruitImageload::load("/img/cactus24x50.bmp",
		DisplayIO::Bitmap,
		DisplayIO::Palette, &palette);
	palette->make_transparent(1);
	palette->set(0, 0x008000);

	TileGrid *cactus2 = new TileGrid(cactus2_bmp, palette);
	cactus2->set_flip_x(true);
	cactus2->set_y(170);
	group->append(cactus2);

	AdafruitImageload *digital_bmp = AdafruitImageload::load("/img/digital200x25.bmp",
		DisplayIO::Bitmap,
		DisplayIO::Palette, &palette);
	palette->make_transparent(1);
	palette->set(0, 0x222222);

	TileGrid *score = new TileGrid(digital_bmp, palette,
								  3,
								  1,
								  20,
								  25);
	score->set_x(176);
	score->set_y(4);
	group->append(score);

	AdafruitImageload *game_over_bmp = AdafruitImageload::load("/img/game_over190x10.bmp",
		DisplayIO::Bitmap,
		DisplayIO::Palette, &palette2);
	palette2->make_transparent(1);
	palette2->set(0, 0xFF0000);

	TileGrid *game_over = new TileGrid(game_over_bmp, palette2);
	game_over->set_x(240);
	game_over->set_y(100);
	game_over->set_hidden(true);
	group->append(game_over);

	AdafruitImageload *cloud_bmp = AdafruitImageload::load("/img/cloud92x27.bmp",
		DisplayIO::Bitmap,
		DisplayIO::Palette, &palette2);
	palette2->make_transparent(15);

	TileGrid *cloud = new TileGrid(cloud_bmp, palette2);
	game_over->set_x(80);
	game_over->set_y(30);
	group->append(cloud);

	display->show(group);

	bool demo = true;

#if DEBUG_TEST
	test1(display, group);
#endif

	while (true) {
		int t = 0;
		int v[] = {-32, -16, -8, -6, -5, -4, -3, -2, -2, -1, -1, -1, -1, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 8, 16, 32};
		int jump = -1;

		int points = 0;
		update_score(score, 0);

		dinosaur->set_y(160);
		cactus->set_x(240);
		cactus2->set_x(480);

		while (true) {
			for(int x = 0; x < 120; ++x) {
				ground->set(x, (t + x) & 0xFF);
			}

			cactus->set_x(cactus->get_x() - 2);
			if (cactus->get_x() < -15) {
				cactus->set_x(cactus2->get_x() + 240 + 2 * os_urandom(1, 0));
				printf("%d, %d\n", cactus->get_x(), cactus2->get_x());
			}

			cactus2->set_x(cactus2->get_x() - 2);
			if (cactus2->get_x() < -24) {
				cactus2->set_x(cactus->get_x() + 240 + 2 * os_urandom(1, 0));
				printf("%d, %d\n", cactus->get_x(), cactus2->get_x());
			}		
		
			if ((t & 7) == 0) {
				cloud->set_x(cloud->get_x() -1);
				if (cloud->get_x() < -92) {
					cloud->set_x(240 + (os_urandom(1, 0) & 0xF));
				}
			}

			if (jump < 0 && button->get_value() == 0) {
				jump = 0;
				dinosaur->set2(0, 0, 2);
				if (demo) {
					demo = false;
					points = 0;
					update_score(score, 0);
					palette->set(0, 0xCCCCCC);
					dinosaur->set_pixel_shader(palette);
				}
			}

			if (demo && jump < 0 && (cactus->get_x() == 52 || cactus2->get_x() == 52)) {
				jump = 0;
				dinosaur->set2(0, 0, 2);
			}

			if (jump >= 0) {
				dinosaur->set_y(dinosaur->get_y() + v[jump]);
				jump += 1;
				if (jump >= (sizeof(v) / sizeof(v[0]))) {
					jump = -1;
				}
			} else {
				if ((t & 7) == 0) {
					dinosaur->set2(0, 0, (t >> 3) & 1);
					//printf("dinosaur->set2 : %d\n",  (t >> 3) & 1);
				}
			}

			if (cactus->get_x() == 0 || cactus2->get_x() == 0) {
				points += 1;
				update_score(score, points);
			}

			display->show(group);

			if ((8 < cactus->get_x() && cactus->get_x() < 36 && (dinosaur->get_y() + 44) >= cactus->get_y()) || 
				(8 < cactus2->get_x() && cactus2->get_x() < 36 && (dinosaur->get_y() + 44) >= (cactus2->get_y()))
				) {
				printf("%d, %d, %d\n", cactus->get_x(), cactus2->get_x(), dinosaur->get_y());
				game_over->set_hidden(false);
				game_over->set_x(25);
				display->show(group);
				time_sleep(1);
				while (button->get_value()) {
					time_sleep(0.1);
				}

				time_sleep(1);
				while (!button->get_value()) {
					time_sleep(0.1);
				}
				game_over->set_x(240);
				game_over->set_hidden(true);
				printf("%s\n", "restart");
				break;
			}

			t = (t + 1) & 0xFF;
			// time_sleep(0.05)
		}
	}

	return 0;
}


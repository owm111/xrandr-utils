#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>

static int includescreen;
static Display *display;
static int screen, width, height;
static XineramaScreenInfo *outputs;
static int noutput;

static void
processargs(int argc, char **argv)
{
	int opt;

	while (opt = getopt(argc, argv, "sv"), opt != -1) switch (opt) {
	case 's':
		includescreen = 1;
		break;
	case 'v':
		puts("qog-0.0");
		exit(EXIT_FAILURE);
		break;
	default:
		fprintf(stderr, "usage: %s [-sv]\n", argv[0]);
		exit(EXIT_FAILURE);
		break;
	}
}

int
main(int argc, char **argv)
{
	int i;

	processargs(argc, argv);
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "%s: XOpenDisplay: Failed to open display\n",
				argv[0]);
		return EXIT_FAILURE;
	}
	screen = DefaultScreen(display);
	height = DisplayHeight(display, screen);
	width = DisplayWidth(display, screen);
	if (includescreen)
		printf("%dx%d+0+0 ", width, height);
	if (XineramaIsActive(display)) {
		outputs = XineramaQueryScreens(display, &noutput);
		for (i = 0; i < noutput; i++)
			printf("%dx%d+%d+%d ", outputs[i].width,
					outputs[i].height, outputs[i].x_org,
					outputs[i].y_org);
		XFree(outputs);
	} else {
		printf("%dx%d+0+0 ", width, height);
	}
	putchar('\n');
	return EXIT_SUCCESS;
}

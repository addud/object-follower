#ifndef colorsensor
#define colorsensor

// Sensor mode command (each bit is sent to the sensor)
#define COLORSENSOR        (0xB0)
#define LIGHTSENSOR_BLUE   (0x08)
#define LIGHTSENSOR_RED    (0x70)
#define LIGHTSENSOR_GREEN  (0xF0)
#define LIGHTSENSOR_NONE   (0x88)

// Color IDs
#define BLACK           (0)
#define DARK_BLUE       (1)
#define LIGHT_BLUE      (2)
#define GREEN           (3)
#define YELLOW          (4)
#define ORANGE          (5)
#define RED             (6)
#define WHITE           (7)
#define UNKNOWN_COLOR   (99)

extern void colorsensor_init(int , unsigned char);
extern void colorsensor_term(int);
extern  int colorsensor_light_get(int);
extern void colorsensor_light_full(int port);
extern  int colorsensor_color_get(int);
extern void colorsensor_rgb_get(int, short int[3]);

#endif //colorsensor


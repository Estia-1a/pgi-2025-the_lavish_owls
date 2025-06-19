#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();

void dimension(const char*);

void first_pixel(char *source_path);

void tenth_pixel(char *source_path);

void max_pixel(char *source_path); 

void second_line(const char *source_path);

void max_component(const char *source_path, char component);

void min_pixel(const char *source_path);

void min_component(const char *source_path, const char component);

void color_green(const char *source_path);

void color_red(const char *source_path);

void color_gray(unsigned char *data, int width, int height, int channels);

void stat_report(const char *filename);

void color_invert(const char *source_path);

void color_blue(const char *source_path);

void rotate_acw(const char *source_path);

void rotate_cw(const char *source_path);

void color_gray_luminance(unsigned char *data, int width, int height, int channels);

void mirror_horizontal(const char *source_path);

void scale_crop(const char *filename, int center_x, int center_y, int crop_width, int crop_height);

void mirror_total(char* filename);

void mirror_vertical(const char *source_path);

void scale_nearest(char *source_path, float coeff);

void color_desaturate(char *source_path);

#endif

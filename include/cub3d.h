#ifndef	CUB3D_H
# define CUB3D_H

# define _USE_MATH_DEFINES

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "libft.h"
#include "keycode.h"
#include "struct.h"
#include <mlx.h>
#include <math.h>

# ifndef BONUS
#  define BONUS 0
# endif

# ifndef BUFFERSIZE
#  define BUFFERSIZE 20
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct	s_main t_main;
typedef struct	s_map t_map;
typedef struct	s_texture t_texture;
typedef struct	s_myimage t_myimage;
typedef struct	s_vec2 t_vec2;
typedef struct	s_keys t_keys;
typedef struct	s_dda_struct t_dda_struct;

/*------------------------------------ DEBUG ---------------------------------*/


void	init_debug(t_main *main);

// MAP AND PARSING//

bool		is_dir(char *file_relative_path);
bool		parsing(t_main *main, char *file);
bool		cub_extension_is_valid(char	*s, int len);
bool		xmp_extension_is_valid(char	*s, int len);

char		*max_strdup(const char *s1, int max_size);
char		**get_file_content(t_main *main, int fd, char *file);

void		is_map_valid(t_main *main);
void		parse_map_elements(t_main *main);
void		get_map_descritpion(t_main *main);
void		extract_colour(t_main *main, char *id, char *info);
void		extract_texture(t_main *main, char *id, char *xpm_f);
void		validate_colour(t_main *main, char **splitted_colours);
bool		find_player_position(t_main *main, int *x, int *y, int *player);

// MINIM	AP //
void		print_fov(t_main *main);
void		print_grid(t_main *main);
void		draw_player(t_main *main);
void		init_minimap(t_main *main);
void		print_minifov(t_main *main);
void		print_minimap(t_main *main);
void		mini_raycasting(t_main *main);
void		print_minimap_base(t_main *main);

t_vec2		mini_dda(t_main *main, double dst_x, double dst_y);


// RENDERING //
int			render_next_frame(t_main *main);

void		init_img(t_main *main);
void		player_movement(t_main *main);
void		put_pixel_to_image(t_main *main, int x, int y, int colour);
void		valid_next_movement_up(t_main *main, double next_x, double next_y);
void		valid_next_movement_down(t_main *main, double next_x, double next_y);
void		valid_next_movement_left(t_main *main, double next_x, double next_y);
void		valid_next_movement_right(t_main *main, double next_x, double next_y);



//GAMELOOP//
void		render_game(t_main *main);

void		draw_wall(t_main *main, t_dda_struct *dda_struct, int x, t_texture texture);
t_texture	get_direction_for_texture(t_main *main, t_dda_struct *dda_struct);

size_t		count_map_height(char **map);

// ERROR HANDLING //
void		print_error_and_message(char *error_message);

// UTILS //
int			has_new_line(char *buffer);
int			get_fd(t_main *main, char *file_relative_path);

char		*get_next_line(int fd);
char		*join_and_free(char *line, char *tmp2);

void		print_array(char **array);
void		normalize_angle(double *angle);
void		ft_strcpy(char *dest, char *src, int start, int end);

double		get_vector_norm(t_vec2 vec1, t_vec2 vec2);

void		digital_differential_analyzer(t_main *main, t_dda_struct *dda_struct);

size_t		string_array_len(char **str);

// FREE FUNCTIONS //
int			handle_destroy(t_main *main);
void		safe_free_tab(void ***ptr);
void		free_mlx_pointers(t_main *main);
void		free_string_array(char ***array);
void		free_ptr_and_set_to_null(char *ptr);
void		free_all_pointer_arrays(t_main *main);
void		exit_cub3d(t_main *main, char *error_message);

#endif
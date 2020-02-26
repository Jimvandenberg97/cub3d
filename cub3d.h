/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 14:38:09 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/20 15:35:07 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>

/*
** Bonus Catcher
*/

# ifndef BONUS
#  define BONUS 0
# endif

/*
** Keyboard Enums
*/

# define CUB_KEY_FORWARD	13
# define CUB_KEY_LEFT		0
# define CUB_KEY_BACK		1
# define CUB_KEY_RIGHT		2
# define CUB_KEY_ESC		53
# define CUB_KEY_LLEFT		123
# define CUB_KEY_LRIGHT		124
# define CUB_KEY_F3			99
# define CUB_KEY_F12		111

/*
** Texture Enums and count
*/

# define TEXT_COUNT 	12
# define TEXT_NO		0
# define TEXT_SO		1
# define TEXT_WE		2
# define TEXT_EA		3
# define TEXT_SPR		4
# define TEXT_FLOOR		5
# define TEXT_CEIL		6
# define TEXT_SPR_ITEM	7
# define TEXT_SPR_COLL	8
# define TEXT_HWALL		9
# define TEXT_HUD		10
# define TEXT_TRAP		11

# define SPRITE_COUNT	4

/*
** Options Enums and count
*/

# define OPT_COUNT		7
# define OPT_FLOORTEXT	0
# define OPT_CEILTEXT	1
# define OPT_SPR_ITEM	2
# define OPT_SPR_COLL	3
# define OPT_TXT_HWALL	4
# define OPT_TXT_HUD	5
# define OPT_TRAP		6

/*
** Charsets
*/

# define CSET_SPAWN	"NESW"
# define CSET_MAP	"012NESW34HT "
# define CSET_SPR	"234T"
# define CSET_SPR_I	"3T"
# define CSET_SPR_C	"34T"
# define CSET_SPR_T	"T"
# define CSET_HIT	"1H"
# define CSET_COLL	"1"
# define CSET_SKIP	"02NESW34HT "
# define CSET_MINIT	"01234HT "

/*
** Bitmap
*/

# define BMP_FHSIZE		14
# define BMP_IHSIZE		40
# define BMP_BPP		3
# define BMP_EXPNAME	"frame.bmp"
# define BMP_SCRNAME	"screenshot.bmp"

/*
** Settings
*/

# define SET_SPEED_MOV	0.0600
# define SET_SPEED_ROT	0.0285
# define SET_HBSIZE		0.1200

/*
** General Vector struct
*/

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

/*
** Texture data / meta block
*/

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

/*
** Texture wrapper
*/

typedef struct	s_texture
{
	t_data		data;
	int			width;
	int			height;
}				t_texture;

/*
** Sprite types wrapper
*/

typedef struct	s_stypes
{
	char		c;
	int			tex;
	int			enabled;
}				t_stypes;

/*
** Sprite object wrapper
*/

typedef struct	s_sprite
{
	t_vector	pos;
	int			tex;
	double		distance;
	int			hidden;
}				t_sprite;

/*
** Sprite Render Wrapper
*/

typedef struct	s_srender {
	t_vector	spos;
	t_vector	transform;
	t_vector	draw_start;
	t_vector	draw_end;
	int			screenx;
	int			height;
	int			width;
	int			x;
	double		invdet;
}				t_srender;

/*
** Floor / Ceiling wrapper
*/

typedef struct	s_fc
{
	t_vector	raydir0;
	t_vector	raydir1;
	t_vector	floorstep;
	t_vector	floor;
	t_vector	cell;
}				t_fc;

/*
** Keypress tracker [BOOLEAN]
*/

typedef struct	s_keys
{
	int			forward;
	int			left;
	int			back;
	int			right;
	int			lleft;
	int			lright;
}				t_keys;

/*
** Hitbox memory [BOOLEAN]
*/

typedef struct	s_hitbox
{
	double		size;
	int			n;
	int			e;
	int			s;
	int			w;
	int			ne;
	int			se;
	int			sw;
	int			nw;
}				t_hitbox;

/*
** Player memory
*/

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	cam;
	t_vector	ray;
	t_vector	deldist;
	t_vector	sdist;
	double		pwalldist;
	int			bx;
	int			by;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			linestart;
	int			lineend;
	double		health;
	double		score;
	int			items;
}				t_player;

/*
** Gamestate struct
** Mother of all structs....
*/

typedef struct	s_config
{
	int			width;
	int			height;
	char		*paths[TEXT_COUNT];
	int			color_floor;
	int			color_ceil;
	char		**map;
	int			map_height;
	t_player	player;
	t_data		images[2];
	int			img;
	void		*mlx;
	void		*mlx_win;
	t_keys		keys;
	double		speed_move;
	double		speed_rot;
	double		hb_size;
	double		time_old;
	double		time_delta;
	int			debug;
	int			debug_line;
	int			options[OPT_COUNT];
	t_texture	textures[TEXT_COUNT];
	t_stypes	stypes[SPRITE_COUNT];
	t_sprite	*sprites;
	int			spritecnt;
	t_fc		fc;
	double		*zbuff;
	int			save;
	int			bmp_color;
	t_vector	port_start;
	t_vector	port_end;
	int			portrender;
}				t_config;

/*
** Utilities
*/

void			log_error(t_config *cfg, char *msg);
void			log_close(t_config *cfg, char *msg);
void			mem_protect(t_config *cfg, void *ptr, char *msg);
void			vector_set(t_vector *dest, t_vector src);
double			vector_distance(t_vector a, t_vector b);
int				finalize(t_config *cfg);
void			debugger(t_config *cfg);
void			bitmap_export(t_config *cfg, char *fname);
t_vector		vector_new(double x, double y);
int				in_square(t_vector start, t_vector end, t_vector pos);
void			r_wipe(char **data);
void			cleanup(t_config *cfg);

/*
** Map File Parser
*/

void			config_parse(char *path, t_config *cfg);
void			config_init(t_config *cfg);
void			parse_resolution(char *line, t_config *cfg);
void			parse_path(t_config *cfg, char *line, char **var);
void			parse_color(t_config *cfg, char *line, int *color);
void			parse_map(char **map, t_config *cfg);
void			map_validate(t_config *cfg);
int				config_ready(t_config *cfg);
void			spawn_setrotation(t_config *cfg, char c);
int				parse_sound(char *line, t_config *cfg);
void			floodfill(t_config *cfg, int x, int y, char **map);
char			**map_dupe(t_config *cfg);

/*
** Color converting
*/

int				color_a(int color);
int				color_r(int color);
int				color_g(int color);
int				color_b(int color);
int				color_argb(int a, int r, int g, int b);
int				color_correct(int color, double multiplier);

/*
** Engine
*/

void			render_run(t_config *cfg);
void			engine_init(t_config *cfg);
void			pixel_put(t_data *data, int x, int y, int color);
void			line_put(int x, t_config *cfg, int tex);
void			image_init(t_config *cfg, t_data *img, void *mlx);
void			move_run(t_config *cfg);
void			look_run(t_config *cfg);
t_hitbox		hitbox_calc(t_config *cfg, t_vector pos);
void			textures_init(t_config *cfg);
int				get_px(t_texture tex, t_vector pos, int mirror);
int				get_screen_px(t_data *data, int x, int y);
void			render_floor(t_config *cfg);
void			ray_render(t_config *cfg, int x, t_player *p);
void			ray_calc(t_player *p, int x, double w);
void			ray_cast(t_config *cfg, t_player *p);

/*
** Sprites
*/

void			sprites_init(t_config *cfg);
void			sprites_allocate(t_config *cfg);
void			sprites_save(t_config *cfg, int *spos);
void			quicksort(t_sprite *sprites, int first, int last);
void			sprites_distcalc(t_config *cfg);
void			sprites_render(t_config *cfg);
void			item_pickup(t_config *cfg, int x, int y);

/*
** Hudz
*/

void			draw_square(t_config *cfg, t_vector a, t_vector b, int color);
void			hud_draw(t_config *cfg);
void			hud_viewport(t_config *cfg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:59:47 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/22 21:51:19 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE_PRINTF 4096
# define SPECIFIERS "%cspdiuxX"
# define HEXADE_LOWER "0123456789abcdef"
# define HEXADE_UPPER "0123456789ABCDEF"
# define DIGITS "0123456789"
# define FLAGS "+ 0-#"

typedef union u_nbr_union
{
	unsigned long	uint64;
	long			int64;
}					t_nbr_union;

typedef enum e_bases
{
	NOT_SET = 0,
	BASE_10 = 10,
	BASE_16 = 16
}					t_bases_e;

typedef enum e_rtrns
{
	OK_PRINTF = 0,
	MALLOC_ERR = -2,
	PARSE_ERR = -3,
	PRINTF_ERR = -1
}					t_rtrns_e;

typedef enum e_nbr_track
{
	NEG_NBR = -1,
	NOT_MODIFIED = 0,
	CONVERTED_FRM_NEG = 1
}					t_nbr_track_e;

typedef struct s_fmt_flags
{
	t_nbr_track_e	nbr_track;
	t_bases_e		base_e;
	bool			left_justif_fl;
	bool			plus_fl;
	bool			space_fl;
	bool			hasht_fl;
	bool			zero_pad_fl;
	bool			precision_fl;
	bool			nbr_upper_case;
	bool			is_signed_nbr;
	char			specifier;
	int				width_val;
	int				precision_val;
	int				padding_spaces_nbr;
	int				padding_zeros_nbr;
}					t_fmt_flags_s;

typedef struct s_nbr_bfr
{
	char			nbr_bfr[64];
	int				nbr_bfr_len;
}					t_nbr_bfr;

typedef struct s_data
{
	t_fmt_flags_s	flags_s;
	t_nbr_union		dynmc_nbr;
	t_nbr_bfr		nbr_s;
	const char		*str;
	va_list			ap;
	int				rtrn_printf_value;
	char			*printf_buffer;
	int				printf_buf_len;
}					t_data_s;

int					ft_parse_fmt(t_data_s *data_s);
void				ft_render_into_buffer(t_data_s *data_s);
void				ft_flush_buffer(t_data_s *data_s);
void				ft_render_char_to_buf(t_data_s *data_s, int c);
void				ft_add_n_chrs_into_bfr(t_data_s *data_s, int len, int c);
void				ft_render_str_to_buf(t_data_s *data_s, char *str_arg);
void				ft_add_n_of_str_into_bfr(t_data_s *data_s, int len,
						char *str_arg);
void				ft_render_nbrs_to_buf(t_data_s *data_s);
void				ft_itoa_base_bfr(t_data_s *data_s, t_nbr_union values_uni);
void				ft_set_pad_zeros_nbr_cases(t_data_s *data_s);
void				ft_set_pad_spaces_nbr_cases(t_data_s *data_s);
int					ft_printf(const char *fmt, ...);

#endif

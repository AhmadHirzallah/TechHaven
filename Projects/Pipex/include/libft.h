/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:10:00 by ahirzall          #+#    #+#             */
/*   Updated: 2025/02/22 17:29:51 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_value_type
{
	VAL_PTR,
	VAL_LONG,
	VAL_INT,
	VAL_SHORT,
	VAL_CHAR,
	VAL_ULONG,
	VAL_UINT,
	VAL_USHORT,
	VAL_UCHAR,
	VAL_FLOAT,
	VAL_DOUBLE,
	VAL_INVALID
}					t_value_type;

typedef union u_value_data
{
	size_t			as_size_t;

	void			*as_ptr;

	long			as_long;

	int				as_int;

	short			as_short;

	char			as_char;

	unsigned long	as_ulong;

	unsigned int	as_uint;

	unsigned short	as_ushort;

	unsigned char	as_uchar;

	float			as_float;

	double			as_double;

	int				*as_int_ptr;
}					t_value_data;

typedef struct s_value
{
	t_value_type	type;
	t_value_data	data;
}					t_value;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief Allocates and returns a new node.
 * The member variable 'content' is initialized with
 * the value of the parameter 'content'.
 * The variable 'next' is initialized to NULL.
 *
 * @param content The content to create the node with.
 * @return t_list* The new node.
 *
 * @example
 * t_list *node = ft_lstnew("Hello");
 * // Creates a new node with content "Hello".
 */
t_list				*ft_lstnew(void *content);

/**
 * @brief Adds the node 'new' at the beginning of the list.
 *
 * @param lst The address of a pointer to the first link of a list.
 * @param new The node to be added to the list.
 *
 * @example
 * ft_lstadd_front(&my_list, new_node);
 * // Adds new_node to the beginning of my_list.
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Counts the number of nodes in a list.
 *
 * @param lst The beginning of the list.
 * @return int The length of the list.
 *
 * @example
 * int size = ft_lstsize(my_list);
 * // Returns the number of elements in my_list.
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief Returns the last node of the list.
 *
 * @param lst The beginning of the list.
 * @return t_list* The last node of the list.
 *
 * @example
 * t_list *last = ft_lstlast(my_list);
 * // Returns the last node of my_list.
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief Adds the node 'new' at the end of the list.
 *
 * @param lst The address of a pointer to the first link of a list.
 * @param new The node to be added to the list.
 *
 * @example
 * ft_lstadd_back(&my_list, new_node);
 * // Adds new_node to the end of my_list.
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Takes a node and frees the memory of the node’s content
 * using the function 'del' given as a parameter and frees the node.
 * The memory of 'next' must not be freed.
 *
 * @param lst The node to free.
 * @param del The function used to delete the content.
 *
 * @example
 * ft_lstdelone(node, free);
 * // Frees the memory of node and its content.
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Deletes and frees the given node and every successor of that node,
 * using the function 'del' and free(3). Finally,
	the pointer to the list must be set to NULL.
 *
 * @param lst The address of a pointer to a node.
 * @param del The function used to delete the content of each node.
 *
 * @example
 * ft_lstclear(&my_list, free);
 * // Frees the entire list and its contents.
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**

	* @brief Iterates the list 'lst' and applies
	'f' func on the content of each node.
 *
 * @param lst The address of a pointer to a node.
 * @param f The function to apply to each node's content.
 *
 * @example
 * void print_content(void *content) { printf("%s\n", (char *)content); }
 * ft_lstiter(my_list, print_content);
 * // Prints the content of each element in my_list.
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**

	* @brief Iterates the list 'lst'
	and applies the function 'f' on the content of each node.

	* Creates a new list resulting from
		the successive applications of the function 'f'.
 * The 'del' function is used to delete the content of a node.
 *
 * @param lst The address of a pointer to a node.
 * @param f The function used to iterate on the list.
 * @param del The function used to delete the content of a node if needed.
 * @return t_list* The new list. NULL if the allocation fails.
 *
 * @example

	* void *duplicate_content(void *content)
	{ return (ft_strdup((char *)content)); }
 * t_list *new_list = ft_lstmap(my_list, duplicate_content, free);
 * // Creates a new list with duplicated contents.
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**

	* @brief Allocates memory for an array of `count` elements of `size` bytes each,
 * and initializes all bytes to 0.
 *
 * @param count Number of elements to allocate.
 * @param size Size of each element.
 * @return void* Pointer to the allocated memory.
 * Returns NULL if allocation fails.
 *
 * @example
 * int *arr = ft_calloc(5, sizeof(int));
 * // Allocates memory for 5 integers, all initialized to 0.
 * // The array can be accessed as arr[0], arr[1], etc.
 */
void				*ft_calloc(size_t count, size_t size);

/**
 * @brief Fills the first `len` bytes of the memory area pointed to by `b`
 * with the byte `c`.
 *
 * @param b Pointer to the memory area.
 * @param c Byte to fill the memory with.
 * @param len Number of bytes to fill.
 * @return void* Pointer to the memory area `b`.
 *
 * @example
 * char str[10];
 * ft_memset(str, 'A', 9);
 * str[9] = '\0';
 * // Fills the first 9 characters of `str` with 'A',
 * then null-terminates the string.
 * // The result will be: "AAAAAAAAA".
 */
void				*ft_memset(void *b, int c, size_t len);

/**
 * @brief Fills the first `n` bytes of the memory area pointed to by `s`
 * with zeroes.
 *
 * @param s Pointer to the memory area.
 * @param n Number of bytes to zero out.
 *
 * @example
 * char str[5] = "abcd";
 * ft_bzero(str, 3);
 * // The first three characters of `str` will be set to zero.
 * // The result will be: "\0\0\0d".
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief Copies `n` bytes from memory area `src` to memory area `dst`.
 *
 * @param dst Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return void* Pointer to `dst`.
 *
 * @example
 * char src[5] = "abcd";
 * char dst[5];
 * ft_memcpy(dst, src, 5);
 * // Copies the content of `src` to `dst`, including the null terminator.
 * // `dst` will now contain: "abcd".
 */
void				*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief Copies `len` bytes from `src` to `dst`,
 * handling overlapping memory areas.
 *
 * @param dst Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param len Number of bytes to copy.
 * @return void* Pointer to `dst`.
 *
 * @example
 * char str[] = "abcdef";
 * ft_memmove(str + 2, str, 4);
 * // Moves the first 4 characters to start at index 2.
 * // The result will be: "ababcd".
 */
void				*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief Scans the initial `n` bytes of the memory area `s`
 * for the byte `c`.
 *
 * @param s Pointer to the memory area.
 * @param c Byte to locate.
 * @param n Number of bytes to scan.
 * @return void* Pointer to the matching byte,
 * or NULL if the byte isn't found.
 *
 * @example
 * char str[] = "Hello, World!";
 * char *result = ft_memchr(str, 'o', 5);
 * // Scans the first 5 bytes of `str` for the byte 'o'.
 * // The result will be a pointer to 'o' in "Hello".
 */
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares the first `n` bytes of the memory areas `s1` and `s2`.
 *
 * @param s1 Pointer to the first memory area.
 * @param s2 Pointer to the second memory area.
 * @param n Number of bytes to compare.
 * @return int An integer less than, equal to,
 * or greater than zero if `s1` is found, respectively,
 * to be less than, to match, or be greater than `s2`.
 *
 * @example
 * char str1[] = "abcdef";
 * char str2[] = "abcxyz";
 * int result = ft_memcmp(str1, str2, 3);
 * // Compares the first 3 bytes of `str1` and `str2`.
 * // The result will be 0, since "abc" == "abc".
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Calculates the length of the string `s`,
 * excluding the terminating null byte.
 *
 * @param s Pointer to the string.
 * @return size_t The number of characters in the string.
 *
 * @example
 * char str[] = "Hello, Wostatic void	*malloc_gc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	return (ptr);
}

static char	*strnew(size_t size)
{
	return ((char *) malloc_gc(sizeof(char) * (size + 1)));
}
rld!";
 * size_t length = ft_strlen(str);
 * // The result will be 13, the length of "Hello, World!".
 */
size_t				ft_strlen(const char *s);

/**
 * @brief Copies up to `dstsize` - 1 characters from the string `src`
 * to `dst`,
 * null-terminating the result if `dstsize` is not 0.
 *
 * @param dst Pointer to the destination buffer.
 * @param src Pointer to the source string.
 * @param dstsize Size of the destination buffer.
 * @return size_t The total length of the string `src`.
 *
 * @example
 * char dst[6];
 * size_t result = ft_strlcpy(dst, "Hello, World!", sizeof(dst));
 * // Copies "Hello" into `dst` (5 characters plus null-terminator).
 * // The result will be 13, which is the full length of "Hello, World!".
 */
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief Duplicates the string `s1`, allocating memory for the new string.
 *
 * @param s1 Pointer to the string to duplicate.
 * @return char* Pointer to the newly allocated duplicate string,
 * or NULL if memory allocation fails.
 *
 * @example
 * char *dup = ft_strdup("Hello");
 * // `dup` will be a new string with the content "Hello".
 * // You need to free the memory allocated for `dup` when done.
 */
char				*ft_strdup(const char *s1);

/**
 * @brief Appends the string `src` to `dst`,
 * ensuring that `dst` is null-terminated
 * and the total size of the destination buffer is `dstsize`.
 *
 * @param dst Pointer to the destination buffer.
 * @param src Pointer to the source string.
 * @param dstsize Size of the destination buffer.
 * @return size_t The total length of the string `dst` would have been
 * if there were enough space.
 *
 * @example
 * char dst[10] = "Hello";
 * ft_strlcat(dst, ", World!", sizeof(dst));
 * // Appends ", World!" to `dst`, but since `dst` is too small,
 * the result will be "Hello, Wo".
 */
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief Locates the first occurrence of the character `c`
 * in the string `s`.
 *
 * @param s Pointer to the string.
 * @param c Character to locate.
 * @return char* Pointer to the first occurrence of `c`,
 * or NULL if `c` is not found.
 *
 * @example
 * char *result = ft_strchr("Hello, World!", 'W');
 * // `result` will point to the "World!" part of the string.
 */
char				*ft_strchr(const char *s, int c);

/**
 * @brief Locates the last occurrence of the character `c` in the string `s`.
 *
 * @param s Pointer to the string.
 * @param c Character to locate.
 * @return char* Pointer to the last occurrence of `c`,
 * or NULL if `c` is not found.
 *
 * @example
 * char *result = ft_strrchr("Hello, World!", 'o');
 * // `result` will point to the "o" in "World!".
 */
char				*ft_strrchr(const char *s, int c);

/**
 * @brief Locates the first occurrence of the substring `needle`
 * in the string `haystack`,
 * but only searches up to `len` characters.
 *
 * @param haystack The string to search in.
 * @param needle The substring to search for.
 * @param len Maximum number of characters to search.
 * @return char* Pointer to the beginning of the located substring,
 * or NULL if the substring is not found.
 *
 * @example
 * char *result = ft_strnstr("Hello, World!", "World", 8);
 * // Since we only search up to 8 characters, "World" will not be found.
 * // The result will be NULL.
 */
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

/**
 * @brief Compares up to `n` characters of the strings `s1` and `s2`.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return int An integer less than, equal to,
 * or greater than zero if `s1` is found,
 * respectively, to be less than, to match, or to be greater than `s2`.
 *
 * @example
 * int result = ft_strncmp("abc", "abd", 2);
 * // The result will be 0,
 * since the first two characters "ab" are equal in both strings.
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Converts the string `str` to an integer.
 *
 * @param str The string to convert.
 * @return int The converted integer value.
 *
 * @example
 * int result = ft_atoi("42");
 * // The result will be 42.
 */
int					ft_atoi(const char *str);

/**
 * @brief Checks if the given character `c` is an alphabetic letter.
 *
 * @param c The character to check.
 * @return int 1 if `c` is alphabetic, 0 otherwise.
 *
 * @example
 * int result = ft_isalpha('A');
 * // The result will be 1 since 'A' is alphabetic.
 */
int					ft_isalpha(int c);

/**
 * @brief Checks if the given character `c` is a digit.
 *
 * @param c The character to check.
 * @return int 1 if `c` is a digit, 0 otherwise.
 *
 * @example
 * int result = ft_isdigit('5');
 * // The result will be 1 since '5' is a digit.
 */
int					ft_isdigit(int c);

/**
 * @brief Checks if the given character `c` is alphanumeric
 * (either a letter or a digit).
 *
 * @param c The character to check.
 * @return int 1 if `c` is alphanumeric, 0 otherwise.
 *
 * @example
 * int result = ft_isalnum('A');
 * // The result will be 1 since 'A' is alphanumeric.
 */
int					ft_isalnum(int c);

/**
 * @brief Checks if the given character `c` is part of the ASCII
 * character set.
 *
 * @param c The character to check.
 * @return int 1 if `c` is an ASCII character, 0 otherwise.
 *
 * @example
 * int result = ft_isascii(128);
 * // The result will be 0 since 128 is not a valid ASCII character.
 */
int					ft_isascii(int c);

/**
 * @brief Checks if the given character `c` is printable (including space).
 *
 * @param c The character to check.
 * @return int 1 if `c` is printable, 0 otherwise.
 *
 * @example
 * int result = ft_isprint(' ');
 * // The result will be 1 since a space is a printable character.
 */
int					ft_isprint(int c);

/**
 * @brief Converts the given character `c` to uppercase
 * if it is a lowercase letter.
 *
 * @param c The character to convert.
 * @return int The uppercase equivalent of `c`, or `c`
 * if it is not a lowercase letter.
 *
 * @example
 * int result = ft_toupper('a');
 * // The result will be 'A'.
 */
int					ft_toupper(int c);

/**
 * @brief Converts the given character `c` to lowercase
 * if it is an uppercase letter.
 *
 * @param c The character to convert.
 * @return int The lowercase equivalent of `c`, or `c`
 * if it is not an uppercase letter.
 *
 * @example
 * int result = ft_tolower('A');
 * // The result will be 'a'.
 */
int					ft_tolower(int c);

/**
 * @brief Applies the function `f` to each character of the string `s`,
 * passing its index as the first argument.
 *
 * @param s The string to iterate over.
 * @param f The function to apply to each character and its index.
 *
 * @example
 * void to_upper(unsigned int i, char *c) { *c = ft_toupper(*c); }
 * char str[] = "hello";
 * ft_striteri(str, to_upper);
 * // Converts each character in `str` to uppercase.
 * // The result will be "HELLO".
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Applies the function `f` to each character of the string `s`
 * and its index, returning a new string.
 *
 * Allocates (with malloc) and
 * returns a new string resulting from the successive applications
 * of the function `f` to each character of the string `s`.
 * The function `f` is passed the index
 * of the character as its first argument.
 *
 * @param s The string to map over.
 * @param f The function to apply to each character and its index.
 * @return char* A new string with the transformed characters,
 * or NULL if memory allocation fails.
 *
 * @example
 * char to_upper(unsigned int i, char c) { return (ft_toupper(c)); }
 * char *str = ft_strmapi("hello", to_upper);
 * // The result will be "HELLO", a newly allocated string.
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Allocates (with malloc) and returns a new string,
 * which is the result of the concatenation of `s1` and `s2`.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return char* A newly allocated concatenated string,
 * or NULL if memory allocation fails.
 *
 * @example
 * char *joined = ft_strjoin("Hello, ", "World!");
 * // The result will be "Hello, World!", a newly allocated string.
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc) and
 * returns a copy of `s1` with the characters specified in `set`
 * removed from the beginning and the end.
 *
 * @param s1 The string to trim.
 * @param set The set of characters to remove from the beginning
 * and end of the string.
 * @return char* A newly allocated trimmed string,
 * or NULL if memory allocation fails.
 *
 * @example
 * char *trimmed = ft_strtrim("   Hello, World!   ", " ");
 * // The result will be "Hello, World!", a newly allocated string.
 */
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Splits a string into an array of substrings using a delimiter.
 *
 * This function takes a string `s` and splits it into an array of
 * null-terminated substrings, separated by the character `c`.
 * The array of substrings is dynamically allocated, and the last
 * element of the array is set to `NULL` to indicate the end.
 *
 * @param s The input string to be split.
 * @param c The delimiter character used to separate substrings in the string.
 * @return char** A null-terminated array of substrings. If memory allocation
 * fails or if `s` is NULL, the function returns NULL.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 * array and the individual substrings.
 *
 * @example
 * char **result = ft_split("Hello,World,42", ',');
 * The resulting array would be:
 * result[0] = "Hello"
 * result[1] = "World"
 * result[2] = "42"
 * result[3] = NULL
 */
char				**ft_split(char const *str, char delimiter);

/**
 * @brief Converts an integer `n` to a null-terminated string.
 *
 * Allocates (with malloc) and returns a string representing the integer `n`.
 *
 * @param n The integer to convert.
 * @return char* A newly allocated string representing the integer,
 * or NULL if memory allocation fails.
 *
 * @example
 * char *str = ft_itoa(123);
 * // The result will be "123", a newly allocated string.
 */
char				*ft_itoa(int n);

/**
 * @brief Outputs the character `c` to the given file descriptor.
 *
 * @param c The character to output.
 * @param fd The file descriptor to output to.
 *
 * @example
 * ft_putchar_fd('A', 1);
 * // The result will be the character 'A' printed to the standard output
 * (file descriptor 1).
 */
void				ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string `s` to the given file descriptor.
 *
 * @param s The string to output.
 * @param fd The file descriptor to output to.
 *
 * @example
 * ft_putstr_fd("Hello, World!", 1);
 * // The result will be "Hello, World!" printed to the standard output
 * (file descriptor 1).
 */
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs the string `s` to the given file descriptor
 * followed by a newline.
 *
 * @param s The string to output.
 * @param fd The file descriptor to output to.
 *
 * @example
 * ft_putendl_fd("Hello, World!", 1);
 * // The result will be "Hello, World!" printed to the standard output,
 * followed by a newline.
 */
void				ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs the integer `n` to the given file descriptor.
 *
 * @param n The integer to output.
 * @param fd The file descriptor to output to.
 *
 * @example
 * ft_putnbr_fd(42, 1);
 * // The result will be "42" printed to the standard output
 * (file descriptor 1).
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief Allocates (with malloc) and
 * returns a substring from the string `s`,
 * starting at index `start` and of length `len`.
 *
 * @param s The source string.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 * @return char* A newly allocated substring,
 * or NULL if memory allocation fails.
 *
 * @example
 * char *substr = ft_substr("Hello, World!", 7, 5);
 * // The result will be "World", a newly allocated string.
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**split_multi(const char *s, const char *delimiters);
char				*str_tok_sttc(char *str, const char *delimiters);
void				str_nullify_delimiters(char *input, const char *delimiters);
int					ft_atol(const char *nptr);
short				is_str_space(int chr);
__int128			ft_atoint128(const char *nptr);
char				*nbr_to_str(__int128_t nbr);
size_t				str_cmpr(const char *s1, const char *s2);
void				free_2d_arr(char **split);

#endif
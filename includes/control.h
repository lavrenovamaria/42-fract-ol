/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:44 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/09 23:13:38 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_H

# define CONTROL_H

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define KEY_UP				126
# define KEY_DOWN			125
# define KEY_LEFT			123
# define KEY_RIGHT			124
# define KEY_PRESS			2

# define MAIN_PAD_ESC		53
# define MAIN_PAD_SPACE		49
# define MAIN_PAD_C			8
# define MAIN_PAD_H			4
# define MAIN_PAD_R			15
# define MAIN_PAD_PLUS		24
# define MAIN_PAD_MINUS		27

# define MASK_KEY_PRESS			1L
# define MASK_KEY_RELEASE		2L
# define MASK_WHEEL				4L
# define MASK_BUTTON_RELEASE	8L
# define MASK_POINTER_MOTION	64L
# define MASK_EXPOSE			32768L
# define MASK_DESTROY			131072L

# define ZOOM_PLUS				1.2
# define ZOOM_MINUS				0.8
# define SHIFT					0.11

#endif

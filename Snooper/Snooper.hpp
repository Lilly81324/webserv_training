/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snooper.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikunne <sikunne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:42:12 by sikunne           #+#    #+#             */
/*   Updated: 2025/08/08 17:48:17 by sikunne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNOOPER_HPP
# define SNOOPER_HPP

# include <iostream>
# include <sys/types.h>
# include <unistd.h>
# include <dirent.h>

# define MAX_FILES_SHOWN 1000000

class Snooper
{
	private:
		std::string		_path;
		DIR 			*folder;
		struct dirent	*entry;
		void			setFolder(void);
		void			showEntry(const struct dirent *target);
	public:
		Snooper();
		Snooper(const std::string &path);
		Snooper(const Snooper &other);
		~Snooper();
		void			changePath(const std::string &path);
		void			nextEntry(void);
		std::string		getPath(void);
		DIR				*getFolder(void);
		void	showOneFile(void);
		void	showNextFile(void);
		void	showRestFiles(void);
		void	showAllFiles(void);
};

#endif
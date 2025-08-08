/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snooper.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikunne <sikunne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:46:53 by sikunne           #+#    #+#             */
/*   Updated: 2025/08/08 18:10:12 by sikunne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snooper.hpp"

Snooper::Snooper(void): _path("/"), folder(NULL), entry(NULL)
{
	this->setFolder();
}

Snooper::Snooper(const std::string &path): _path(path), folder(NULL), entry(NULL)
{
	this->setFolder();
}

Snooper::~Snooper(void)
{
	if (this->folder)
	{
		closedir(this->folder);
		this->folder = NULL;
	}
}

/**
 * Changes the path of Snooper
 */
void	Snooper::changePath(const std::string &path)
{
	this->_path = path;
	this->setFolder();
}

/**
 * @returns path of Snooper
 */
std::string	Snooper::getPath(void)
{
	return (this->_path);
}

/**
 * Updates folder based on path
 * Can be used to open a new folder
 * Closes old folder and resets entries to first new entry
 */
void	Snooper::setFolder(void)
{
	this->entry = NULL;
	if (this->folder)
		closedir(this->folder);
	this->folder = opendir((this->_path).c_str());
	if (!this->folder)
	{
		std::cerr << "Error opening " << this->getPath() << std::endl;
		return ;
	}
	this->nextEntry();
}

/**
 * @returns pointer to current folder attribute;
 */
DIR *Snooper::getFolder(void)
{
	return (this->folder);
}

/**
 * Skips to next entry in folder
 */
void	Snooper::nextEntry(void)
{
	this->entry = readdir(this->getFolder());
}

/**
 * Displays the target entry on stdout
 * @param target: Entry to display
 */
void	Snooper::showEntry(const struct dirent *target)
{
	if (target == NULL)
	{
		std::cout << "----END OF FILES----" << std::endl;
		return ;
	}
	std::cout << "--------FILE--------" << std::endl;
	std::cout << "Filename: [" << target->d_name << "]" << std::endl;
	std::cout << "Filetype: [" << target->d_type << "]" << std::endl;
	std::cout << "Length:   [" << target->d_reclen << "]" << std::endl;
	std::cout << "Inode Number: [" << target->d_ino << "]" << std::endl;
	std::cout << "Filetype: [" << target->d_type << "]" << std::endl;
}

/**
 * Displays the current File
 */
void	Snooper::showOneFile(void)
{
	showEntry(this->entry);
}

/**
 * Displays the current file and moves to the next one
 */
void	Snooper::showNextFile(void)
{
	showOneFile();
	nextEntry();
}

/**
 * Displays all files left to read, and moves to the end
 */
void	Snooper::showRestFiles(void)
{
	int	i = -1;
	showEntry(this->entry);
	while (++i < MAX_FILES_SHOWN && this->entry)
	{
		nextEntry();
		showOneFile();
	}
}

/**
 * Resets current directory and prints it out again
 */
void	Snooper::showAllFiles(void)
{
	this->changePath(this->getPath());
	this->showRestFiles();
}

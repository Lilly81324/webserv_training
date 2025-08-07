/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_server.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikunne <sikunne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:16:20 by sikunne           #+#    #+#             */
/*   Updated: 2025/08/07 18:28:40 by sikunne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>

int main(void)
{
	int	sock_fd;
	struct sockaddr_in addr;

	// Make adress object
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8080);

	// Make socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Bind socket to object
	bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));

	// Listen for packages
	listen(sock_fd, 1);
	
}
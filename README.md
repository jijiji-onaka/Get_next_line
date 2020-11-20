# Get_next_line
42Tokyoの課題。
ファイルから改行までの1文を読み取り、ファイルの最後まで読み取ります。

42Tokyo project.
Read one sentence from a file, up to the line break, and repeat it to the end of the file.

## Installation
> ```git clone git@github.com:jijiji-onaka/Get_next_line.git && cd Get_next_line```

これで、このリポジトリの階層に移動します。

## Usage

そして、下のようなmain関数を書いて
```gcc get_next_line.c get_next_line_utils.c libft.a -D BUFFER_SIZE=<読み取りたいbyte>```
とコンパイルすると実行できます。

Go to the hierarchy of this repository.
Then, write the main function as shown below.
```gcc get_next_line.c get_next_line_utils.c libft.a -D BUFFER_SIZE=<byte to read>```
You can compile and run in this way.

```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int		fd;
	int		rc;
	char	*line;

	fd = open("<読み取りたいファイル名 : filename you want to read>", O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((rc = get_next_line(fd, &line)) >= 0)
	{
		printf("%s\n", line);
		free(line);
		if (rc == 0)
			break ;
	}
	if (rc < 0)
		return (-1);
}
```

# include "minishell.h"

int	ft_len (int n)
{
    int len;

    len = 0;
    if (n == 0)
        return (len + 1);
    if (n > 0) 
    {
        while (n > 0)
        {
            n = n / 10;
            len ++;
        }
    }
    if (n < 0)
    {
        len = 1;
        n = -1 * n;
        while (n > 0)
        {
            n = n / 10;
            len ++;
        }
    }
    return (len);
}

char	ft_base(int number)
{
    char base[10] = "0123456789";

    return(base[number]);
}

char	*ft_itoa(int n)
{
    char *str;
    unsigned int i;
    unsigned int number;
    unsigned int len;

    len = ft_len(n);
    i = len - 1;
    str = malloc((len + 1) * sizeof(char));
    if (!str || len == 0)
        return(NULL);
    if (n == 0)
    {
        str[i] = ft_base(n);
    }
    if (n < 0)
    {    
        n = -1 * n; 
        while (i > 0)
        {
            number = n % 10;
            str[i] = ft_base(number);
            i--; 
            if (n > 9)
                n = n / 10;
            if (n > 0 && n <= 9 )
            {   
                str[i] = ft_base(n);
                n = n / 10;
                i--;
            }
            if (n == 0)
                str[i] = '-';
        }      
    }
    if (n > 0)
    {
        while (i > 0)
        {
            number = n % 10;
            str[i] = ft_base(number);
            i--; 
            if (n > 9)
                n = n / 10;
            if(n <= 9)
                str[i] = ft_base(n);
        } 
    }  
    str[len] = '\0';
	return (str);
}
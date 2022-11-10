
#POSTFIX ARITHMETIC EXPRESSIONS EVALUATION KATAS IN C
What humans suddently decided collectively decided to put verbs at the end of all sentences!
```
He cracked RSA -> HE RSA CRACKED
I love something mysterious animating every frame of this universe
I something mysterious animating every frame of this universe love
```
Wouldn't be Great?
The our intent in this repo is to put arithmetic operations at the end of arithmetic expressions (What about real languages?)
```
$ ./evaluator "2 2 +"
result: 4

./evaluator "2 2 + 3 *"
result: 12

./evaluator "2 2 + 3 * 6 /"
result: 2
```

Look at what it cost me to split a string in C -- thanks to you strtok documentation.

```c
int extract_tokens(char *s, char *delim1, char *delim2, char **dst, int *sz) {
  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;
  int j, i = 0;

  for (j = 1, str1 = s; ; j++, str1 = NULL) {
    token = strtok_r(str1, delim1, &saveptr1);
    if (token == NULL)
      break;
    for (str2 = token; ; str2 = NULL) {
      subtoken = strtok_r(str2, delim2, &saveptr2);
      if (subtoken == NULL) break;
      dst[i++] = strdup(subtoken);
    }
  }
  *sz = i;
}
Wild isn't it?
```

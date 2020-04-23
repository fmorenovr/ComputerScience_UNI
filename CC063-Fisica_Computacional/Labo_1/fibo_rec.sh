fibonacci(){
    case $1 in 0|1)
      echo -n "$1 ";;
    *)
      echo -n "$(( $(fibonacci $(($1-1)))+$(fibonacci $(($1-2))) )) ";;
    esac
}
echo -n "Ingrese la cantidad de términos: "
read num
echo "La secuencia de fibonacci es: "
for ((i=1;i<=num;i++))
do
    fibonacci $i
done
echo

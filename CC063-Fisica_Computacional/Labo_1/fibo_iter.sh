echo "Ingrese la cantidad de términos: "
read num
echo "La secuencia de fibonacci es: "
f0=0
f1=1
for ((i=0 ; i<=num ; i++))
do
    echo -n "$f1 "
    fn=$((f0+f1))
    f0=$f1
    f1=$fn
done
echo
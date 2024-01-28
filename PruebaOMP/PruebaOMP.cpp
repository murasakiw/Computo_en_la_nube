#include <iostream>//Incluir biblioteca para entrada y salida de datos
#include <omp.h>//Incluir encabezado para utilizar funciones de OMP


#define N 1000 //Definir cantidad de elementos en el arreglo
#define chunk 100 //Definir cantidad de elementos utilizados por hilo para hacer las operaciones
#define mostrar 10 //Definir cantidad de datos a imprimir

//Función para imprimir los resultados
void imprimeArreglo(float* d) 
{
	for (int x = 0; x < mostrar; x++) //Ciclo para iterar el arreglo pasado como argumento
	{
		std::cout << d[x] << " - "; //Imprimir el elemento correspondiente del arreglo
		std::cout << std::endl; //Salto de línea
	}
}

int main()
{
	
	std::cout << "Sumando arreglos en paralelo!\n";
	float a[N], b[N], c[N]; //Definir los arreglos a utilizar como tipo float
	int i; //Definir variable para iterar por los arreglos

	for (i = 0; i < N; i++) //Ciclo para asignar valores a los arreglos a y b
	{
		a[i] = i; //Asignar valor al arreglo a en la posicion i
		b[i] = (i + 1) * 2; //Asignar valor al arreglo b en la posicion i
	}


	int pedazos = chunk;

	//Definir que el siguiente ciclo for se ejecutará paralelamente
	//especificar el número de elementos a utilizar por cada hilo y memoria compartida por hilos 
	//especificar variable i como privada para que sea utilizada de manera independiente por cada hilo
	//establecer planificación estática e indicar el tamaño de los fragmentos del arreglo que tomará cada hilo
	#pragma omp parallel for \
	shared(a, b, c, pedazos) private(i) \
	schedule(static, pedazos)

	for (i = 0; i < N; i++) //Ciclo para realizar la operación de suma con los arreglos
		c[i] = a[i] + b[i]; //Asignar valor al arreglo c de la suma de a + b en la posicion i


	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
	imprimeArreglo(a); //Llamada de la función para imprimir los valores del arreglo a
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
	imprimeArreglo(b); //Llamada de la función para imprimir los valores del arreglo b
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
	imprimeArreglo(c); //Llamada de la función para imprimir los resultados de la suma a+b


}

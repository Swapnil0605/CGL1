#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
#include<stdio.h>

int A[20][3],C[20][3],tx,ty,sx,sy,shx,shy,n;
float B[3][3];

void lineDDA(int x1,int y1,int x2,int y2);

	void translation();
	void scaling();
	void shearing();
	void rotation();
	void reflection();
	void multiply();
	void display();
	void unit();
	
void lineDDA(int x1,int y1,int x2,int y2)
{
	int i,dx,dy,steps;
	float incx,incy,x,y;
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>abs(dy))
	{
		steps=abs(dx);
	}
	else

	{
		steps=abs(dy);
	}
	incx=(float)dx/steps;
	incy=(float)dy/steps;
	x=x1;
	y=y1;
	//glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	for(i=1;i<=steps;i++)
	{
		x=x+incx;
		y=y+incy;
		glVertex2f(round(x),round(y));
	}
	glEnd();
}

void unit()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(i==j)
			{
				B[i][j]=1;
			}
			else
			{
				B[i][j]=0;
			}
		}
	}
}


void translation()
{
	printf("\nEnter the value of tx and ty\n");
	scanf("%d%d",&tx,&ty);
	unit();
	B[2][0]=tx;
	B[2][1]=ty;
	multiply();
}

void scaling()
{
	printf("\nEnter the value of sx and sy\n");
	scanf("%d%d",&sx,&sy);
	unit();
	B[0][0]=sx;
	B[1][1]=sy;
	multiply();
}

void shearing()
{
	int ch;
	printf("\nEnter the choice\n");
	printf("\n1.X axis\n");
	printf("\n2.Y axis\n");
	printf("\n3.XY line\n");
	scanf("%d",&ch);
	unit();
	
	if(ch==1)
	{
		printf("\nEnter the value of shx\n");
		scanf("%d",&shx);
		B[1][0]=shx;
		multiply();
	}
	else
	{
		if(ch==2)
		{
			printf("\nEnter the value shy\n");
			scanf("%d",&shy);
			B[0][1]=shy;
			multiply();
		}
		else
		{
			if(ch==3)
			{
				printf("\nEnter teh value of shx\n");
				scanf("%d",&shx);
				B[1][0]=shx;
				printf("\nEnter the value of shy\n");
				scanf("%d",&shy);
				B[0][1]=shy;
				multiply();
			}
			else
			{
				printf("\nWrong choice\n");
			}
		}
	}
}


void rotation()
{
	float t,ch1;
	printf("\nEnter the value of angle\n");
	scanf("%f",&t);
	float r;
	r=(t*3.14)/180;
	unit();
	printf("\nMenu\n");
	printf("\n1.Clockwise Rotation\n");
	printf("\n2.Anticlockwise Rotation\n");
	printf("\nEnter your choice\n");
	scanf("%f",&ch1);
	if(ch1==1)
	{
		B[0][0]=B[1][1]=cos(r);
		B[1][0]=sin(r);
		B[0][1]=-sin(r);
		multiply();
	}
	else if(ch1==2)
	{
		B[0][0]=B[1][1]=cos(r);
		B[1][0]=-sin(r);
		B[0][1]=sin(r);
		multiply();
	}
	else
		printf("\nWrong Choice.");
}

void reflection()
{
	int ch;
	printf("\nEnter choice\n");
	printf("\n1.About x axis\n");
	printf("\n2.About y axis\n");
	printf("\n3.About X=Y line\n");
	printf("\n4.About x=-y line\n");
	printf("\n5.About Origin\n");
	scanf("%d",&ch);
	unit();
	
	if(ch==1)
	{
		B[1][1]=-1;
		multiply();
	}
	else if(ch==2)
	{
			B[0][0]=-1;
			multiply();
	}
	else if(ch==3)
	{
				B[0][0]=B[1][1]=0;
				B[0][1]=B[1][0]=1;
				multiply();
	}
	else if(ch==4)
	{
					B[0][0]=B[1][1]=0;
					B[1][0]=-1;
					B[0][1]=-1;
					multiply();
	}
	else if(ch==5)
	{
				B[0][0]=B[1][1]=-1;
				multiply();
	}
	else
	{
					printf("\nWrong choice\n");
	}
			
		
			
}


void multiply()
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			C[i][j]=0;
			for(k=0;k<3;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
		C[i][2]=1;
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("\n%d%d",A[i][j],C[i][j]);
		}
	}
}



void Init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	gluOrtho2D(0,640,0,480);
}

void display()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	lineDDA(320,0,320,480);
	lineDDA(0,240,640,240);
	
	glColor3f(0.0,0.0,1.0);
	for(i=0;i<n-1;i++)
	{
	lineDDA(A[i][0]+320,A[i][1]+240,A[i+1][0]+320,A[i+1][1]+240);
	}
	lineDDA(A[n-1][0]+320,A[n-1][1]+240,A[0][0]+320,A[0][1]+240);
	glColor3f(0.0,1.0,0.0);
	
	for(i=0;i<n-1;i++)
	{
	lineDDA(C[i][0]+320,C[i][1]+240,C[i+1][0]+320,C[i+1][1]+240);
	}
	lineDDA(C[n-1][0]+320,C[n-1][1]+240,C[0][0]+320,C[0][1]+240);
	glFlush();
}

int main(int argc,char **argv)
{
	int i,ch;
	printf("\nTransformation\n");
	printf("\n1.translation\n");
	printf("\n2.Scaling\n");
	printf("\n3.Shearing\n");
	printf("\n4.roatation\n");
	printf("\n5.Refleaction\n");
	printf("\nEnteryour choice\n");
	scanf("%d",&ch);
	printf("\nEnter the no. of verices\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\nEnter the value of (x%d,y%d)\n",i+1,i+1);
		scanf("%d%d",&A[i][0],&A[i][1]);
		A[i][2]=1;
	}
	
	switch(ch)
	{
		case 1:
				translation();
				break;
			
		case 2:
				scaling();
				break;
			
		case 3:
				shearing();
				break;
			
		case 4:
				rotation();
				break;
				
		case 5:
				reflection();
				break;
			
		default:
				printf("\nWrong choice\n");
				
	}
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Transformation");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	Init();
	
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}						
										

				


//    
//                            Program  by  KMiNT21
//

//  Пример простейшего каскадирующего прокси под Win32. Правильнее было бы назвать
//  это чем-то вроде "port mapper" или "port redirect". Чтобы было легче
//  разбираться в коде, я даю лишь скелет программы, убрав все лишние строки. 
//  Удачи вам в ваших начинаниях.
//
//
//  (c) KMiNT21 - Ukraine, Zaporizhzhya.   mailto: kmint21@mail.ru  
//      Undeground InformatioN Center [UInC] - http://www.uinc.ru
//

// ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! 
// Если Вы хотите прочесть мою статью "Пишем прокси сервер" с подробнейшим
// комментированием этого исходника или "Синхронные и асинхронные сокеты
// в Windows", то идете на сервере www.uinc.ru в раздел статьи -
// (www.uinc.ru/articles). Первая - будет там в ближайшие дни (а возможно,
// уже там присутствует), а врорая уже есть. Все комментарии шлите на mail.
// ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! 



#include <windows.h>


// НАСТРОЙКА  ПАРАМЕТРОВ
#define IN_PORT     1111
#define OUT_IP      "192.168.0.89"
#define OUT_PORT    80
#define MAX_DATA    100
#define MAXCONN 1000
#define IDE_MSG 110
#define WM_ASYNC_CLIENTEVENT  WM_USER+1
#define WM_ASYNC_PROXYEVENT WM_USER+10

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void ConnectToProxy(SOCKET);


SOCKET hListenSockTCP   = INVALID_SOCKET;
SOCKADDR_IN     myaddrTCP,proxyaddrTCP;
char buf[MAX_DATA];
SOCKET sockets[MAXCONN];
HWND hwndMain;

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szCmdLine,int nCmdShow)
{
  WSADATA stWSADataTCPIP;
  if(WSAStartup(0x0101, &stWSADataTCPIP)) MessageBox(0,"WSAStartup error !","NET ERROR!!!",0); 

  ZeroMemory(sockets,sizeof(sockets));

  WNDCLASS wc;
  memset(&wc,0,sizeof(WNDCLASS));
  wc.style = CS_HREDRAW|CS_VREDRAW |CS_DBLCLKS ;
  wc.lpfnWndProc = (WNDPROC)MainWndProc;
  wc.hInstance = hInst;
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszClassName = "CProxy";
  wc.lpszMenuName = NULL;
  wc.hCursor = LoadCursor(NULL,IDC_ARROW);
  wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
  if (!RegisterClass(&wc)) return 0;

  hwndMain=CreateWindow("CProxy","ProxyExample", WS_MINIMIZEBOX|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_MAXIMIZEBOX|WS_CAPTION|WS_BORDER|WS_SYSMENU|WS_THICKFRAME, CW_USEDEFAULT,0,CW_USEDEFAULT,0, NULL, NULL, hInst, NULL);
  ShowWindow(hwndMain,SW_SHOW);
  

  hListenSockTCP = socket (AF_INET,SOCK_STREAM,0);
  myaddrTCP.sin_family = AF_INET;
  myaddrTCP.sin_addr.s_addr = htonl (INADDR_ANY);
  myaddrTCP.sin_port = htons (IN_PORT);
  if(bind(hListenSockTCP,(LPSOCKADDR)&myaddrTCP, sizeof(struct sockaddr))) { MessageBox(hwndMain,"This port in use!","BIND TCP ERROR!!!",0);} 
  if (listen (hListenSockTCP, 5)) MessageBox(hwndMain,"listen error!","ERROR!!!",0);
  WSAAsyncSelect (hListenSockTCP,hwndMain,WM_ASYNC_CLIENTEVENT,FD_ACCEPT|FD_READ|FD_CLOSE);
  
  
  MSG  msg;
  while(GetMessage(&msg,NULL,0,0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;

  return 0;
}



LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
   WORD WSAEvent;
   int i;
   DWORD currentsock;

  switch (msg)
  {

  case WM_COMMAND:
    break;

  case WM_DESTROY:
    PostQuitMessage(0);  // 10xu4yourtime
    break;


  case WM_ASYNC_CLIENTEVENT: // Сообщения про события сокетов, подключенных к клиенту...
    currentsock = wParam;
    WSAEvent = WSAGETSELECTEVENT (lParam);
    switch (WSAEvent)
    {
      case FD_CLOSE :
           shutdown(sockets[currentsock],1);
           closesocket(currentsock);
           return 0;

      case FD_READ:
           // ПЕРЕНАПРАВЛЕНИЕ ДАННЫХ (redirect). Берем от клиента, посылаем на сервер.
           i=recv(currentsock, buf, MAX_DATA, 0);
                 send(sockets[currentsock],  buf, i, 0); // и отправляем...
           return 0;

      case FD_ACCEPT:
           ConnectToProxy(accept(hListenSockTCP,NULL,NULL));
           return 0;
      }
      break;

  case WM_ASYNC_PROXYEVENT:
       // Найдем соответствующий дескриптор.
       for (i=0;i<MAXCONN;i++)
       if (sockets[i] == wParam) { currentsock=i; break; }
       WSAEvent = WSAGETSELECTEVENT (lParam);
       switch (WSAEvent)
           {
         // Произошло подключение к удаленному хосту
         case FD_CONNECT :
           i=WSAGETSELECTERROR(lParam);
           if (i!=0)
           {
             shutdown(currentsock,1);
             closesocket(sockets[currentsock]);
             sockets[currentsock]=INVALID_SOCKET;
           }
        return 0;
                   
                   
                // Сервер нас отрубает ...
                case FD_CLOSE :
                           shutdown(currentsock,1);
                           closesocket(sockets[currentsock]);    sockets[currentsock]=INVALID_SOCKET;
                           return 0;

                        // Перенаправление данных клиенту
          case FD_READ:
         i=recv(sockets[currentsock], buf, MAX_DATA, 0);
                     send(currentsock,buf, i, 0);
                     return 0;
            }
                break;
  }
  return DefWindowProc(hwnd,msg,wParam,lParam);
}







// Connect to PROXY Connect to PROXY Connect to PROXY Connect to PROXY Connect to PROXY Connect to PROXY

void ConnectToProxy(SOCKET nofsock)
{
  SOCKADDR_IN rmaddr;
  rmaddr.sin_family = AF_INET;
  rmaddr.sin_addr.s_addr = inet_addr(OUT_IP);
  rmaddr.sin_port = htons (OUT_PORT);

  sockets[nofsock] = socket (AF_INET,SOCK_STREAM,0); if(INVALID_SOCKET == sockets[nofsock]) MessageBox(0,"INVALID_SOCKET","ERROR!!!",0);

  WSAAsyncSelect (sockets[nofsock],hwndMain,WM_ASYNC_PROXYEVENT, FD_CONNECT|FD_READ|FD_CLOSE);
  
  connect (sockets[nofsock], (struct sockaddr *)&rmaddr,sizeof(rmaddr));
  
  return;  // Connect OK
}


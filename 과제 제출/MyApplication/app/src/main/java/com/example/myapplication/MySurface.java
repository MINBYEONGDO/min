
package com.example.myapplication;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.Display;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.WindowManager;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

public class MySurface extends SurfaceView implements SurfaceHolder.Callback {
    //SurfaceView
    MyThread mThread;
    SurfaceHolder mHolder;
    Context mContext;
    MissileManager MissileList;
    PlanetManager PlanetList;
    Spaceship ship;
    Timer timer = new Timer();
    Timer ScoreTimer = new Timer();

    Random mRandom = new Random();
    Bitmap screen;
    Bitmap leftKey, rightKey ,missilebutton;//방향키 비트맵
    int leftKeyPosX, leftKeyPosY;//레프트 버튼 좌표값
    int rightKeyPosX, rightKeyPosY;//라이트 버튼 좌표값
    int missileKeyPosX, missileKeyPosY;
    int Width, Height;//넓이, 높이, 해상도
    int button_width;// 버튼 넓이
    int touchPosX, touchPosY;//터치 좌표

    public MySurface(Context context, AttributeSet attrs)//?생성자? 클래스? 클래스는 아닌데
    {

        super(context, attrs);
        SurfaceHolder holder = getHolder();
        holder.addCallback(this);
        this.mContext = context;
        mContext = ((MainActivity)mContext).getApplicationContext();
        mThread = new MyThread(holder, context);

        ship = new Spaceship();
        MissileList = new MissileManager();
        PlanetList = new PlanetManager();
        InitApp();
    }
    //app 초기화 oncreate에서 해야할 코드들 여기다가 하면 됨
    private void InitApp()
    {
        Display display
                = ((WindowManager) mContext.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();

        Width = display.getWidth();
        Height = display.getHeight();

//spaceship = BitmapFactory.decodeResource(getResources(),R.drawable.spaceship);
        // int x = Width/8;
        // int y = Height/11;
        //이미지의 크기를 해상도 기준으로 맞춰준다.
        // spaceship = Bitmap.createScaledBitmap(spaceship,x,y,true);

        // spaceshipPosX =Width * 1/9;
        // spaceShipPoxY = Height * 6/9;

        leftKey = BitmapFactory.decodeResource(getResources(),R.drawable.leftkey);
        leftKeyPosX = Width * 5/9;
        leftKeyPosY = Height*7/9;
        button_width = Width /6;
        leftKey = Bitmap.createScaledBitmap(leftKey, button_width,button_width,true);

        rightKey = BitmapFactory.decodeResource(getResources(), R.drawable.rightkey);
        rightKeyPosX = Width * 7/9;
        rightKeyPosY = Height * 7/9;
        rightKey = Bitmap.createScaledBitmap(rightKey,button_width,button_width,true);

        missilebutton = BitmapFactory.decodeResource(getResources(), R.drawable.missilebutton);
        missileKeyPosX = Width * 3/9;
        missileKeyPosY = Height * 7/9;
        missilebutton= Bitmap.createScaledBitmap(missilebutton,button_width,button_width,true);

        screen = BitmapFactory.decodeResource(getResources(), R.drawable.screen);
        screen = Bitmap.createScaledBitmap(screen, Width, Height, true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder)
    {
//Thread Start
        mThread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder arg0, int format, int width, int height)
    {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder)
    {
    }
    public class Spaceship
    {
        int spaceShipPosX, spaceShipPoxY;//우수전 좌표값
        int spaceshipwidth;
        int spaceshipheight;
        int Score;
        Rect rect;
        boolean blive;
        Bitmap spaceshipBitmap;
        public Spaceship()
        {
            blive = true;
            Score =0;
            spaceshipwidth=120;
            spaceshipheight=160;
            spaceshipBitmap = BitmapFactory.decodeResource(getResources(),R.drawable.spaceship);
            spaceshipBitmap = Bitmap.createScaledBitmap(spaceshipBitmap,spaceshipwidth,spaceshipheight,true);
            spaceShipPosX =100;
            spaceShipPoxY = 1300;
// rect = new Rect(spaceShipPosX, spaceShipPosX+ spaceshipwidth,spaceShipPoxY,spaceShipPoxY+spaceshipheight);
        }
        public void SpaceshipMove(int Number)
        {
            if(Number ==0) //왼쪽
            {
                spaceShipPosX -=20;
            }
            else if(Number ==1)//오른쪽
            {
                spaceShipPosX +=20;
            }
        }
        public void Crush()
        {
            blive = false;
        }
        public void ShipScore(int PlusScore)
        {
            Score += PlusScore;
        }
        public Bitmap GetShipBitmap()
        {
            return spaceshipBitmap;
        }
        public int GetShipX()
        {
            return spaceShipPosX;
        }
        public int GetShipY()
        {
            return spaceShipPoxY;
        }
        public boolean GetShiplive()
        {
            return blive;
        }
        public int GetWidth()
        {
            return spaceshipwidth;
        }
        public int GetHeight()
        {
            return spaceshipheight;
        }
        public int GetScore()
        {
            return Score;
        }
    }

    public class PlanetManager
    {
        Planet PlanetArr;
        int pNumber;
        public PlanetManager()
        {
            PlanetArr = null;
            pNumber=0;
        }
        public void CreatePlanet()
        {
            Planet tmp;
            tmp = new Planet();
            tmp.CreatePlant(pNumber);
            pNumber++;
            if(PlanetArr == null)
                this.PlanetArr = tmp;
            else
            {//★
                Planet temp = PlanetArr;
                while(temp.Next != null)
                {
                    temp = temp.Next;
                }
                temp.Next = tmp;
            }
        }
        public void Move()
        {
            Planet tmp;
            tmp = PlanetArr;
            while(true)
            {
                if(tmp != null)
                {
                    tmp.Move();
                }
                else if(tmp == null)
                    break;
                tmp = tmp.Next;
            }
        }
        public boolean Crush(int x,int y, int width, int height)
        {
            Planet tmp;
            tmp = PlanetArr;
            while(tmp != null)
            {
                if(tmp.Getlive() ==true)
                {
                    if(tmp.GetPlanetY()+tmp.planet_width>=y &&tmp.GetPlanetY()<=y +height)
                    {
                        if (tmp.GetPlanetX() + tmp.Getwidth() >= x && tmp.GetPlanetX() <= x + width) {
                            tmp.blive = false;
                            return true;//출돌했을때
                        }
                    }
                }
                tmp = tmp.Next;
            }
            return false;//출동 안했을때
        }
        public int GetMax()
        {
            return pNumber;
        }
        public int GetX(int number)
        {
            Planet tmp;
            tmp = PlanetArr;
            while(true)
            {
                if(tmp.GetPlanetNumber() != number)
                {
                    tmp = tmp.Next;
                }
                else if(tmp.GetPlanetNumber() == number)
                    break;
            }
            return tmp.GetPlanetX();
        }
        public int GetY(int number)
        {
            Planet tmp;
            tmp = PlanetArr;
            while(true)
            {
                if(tmp.GetPlanetNumber() != number)
                {
                    tmp = tmp.Next;
                }
                else if(tmp.GetPlanetNumber() == number)
                    break;
            }
            return tmp.GetPlanetY();
        }
        public boolean GetPlanetLive(int Number)
        {
            Planet tmp;
            tmp = PlanetArr;
            while(true)
            {
                if(tmp.GetPlanetNumber() != Number)
                    tmp = tmp.Next;
                else if(tmp.GetPlanetNumber() == Number)
                    break;
            }
            return tmp.Getlive();
        }
        public Bitmap GetPlanetBitmap(int Number)
        {
            Planet tmp;
            tmp = PlanetArr;
            while(true)
            {
                if(tmp.GetPlanetNumber() != Number)
                    tmp = tmp.Next;
                else if(tmp.GetPlanetNumber() == Number)
                    break;
            }
            return tmp.GetBitmap();
        }
    }
    public class Planet
    {
        Bitmap PlanetBitmap;
        int RNumber;
        int px;
        int py;
        int PlanetNumber;
        int planet_width;
        boolean blive;
        Planet Next;
        public Planet()
        {
            planet_width = 100;
            Next = null;
            blive = true;
        }

        public void CreatePlant(int Number)
        {
            PlanetBitmap = BitmapFactory.decodeResource(getResources(),R.drawable.planet);
            px =RNumber = mRandom.nextInt(Width-100);
            py =0;
            PlanetBitmap = Bitmap.createScaledBitmap(PlanetBitmap, planet_width, planet_width, true);
            PlanetNumber = Number;
        }
        public void Move()
        {
            if(blive == true)
            {
                if (py < Height)
                    py += 10;
                else if(py >= Height)
                    blive = false;
            }
        }
        public int GetPlanetX()
        {
            return px;
        }
        public int GetPlanetY()
        {
            return py;
        }
        public int GetPlanetNumber()
        {
            return PlanetNumber;
        }
        public int Getwidth()
        {
            return planet_width;
        }
        public boolean Getlive()
        {
            return blive;
        }
        public Planet GetNext(Planet Node)
        {
            return Node.Next;
        }
        public Bitmap GetBitmap()
        {
            return PlanetBitmap;
        }
    }

    public class MissileManager
    {
        Missile MissileArr;
        int MaxNumber;
        public MissileManager()
        {
            MissileArr = null;
            MaxNumber=0;
        }
        public void CreateMissile(int spacex, int spacey)
        {
            Missile tmp;
            tmp = new Missile();
            tmp.CreateMissile( MaxNumber, spacex, spacey);
            MaxNumber++;
            if(MissileArr == null)
                this.MissileArr = tmp;
            else
            {//★
                Missile temp = MissileArr;
                while(temp.Next != null)
                {
                    temp = temp.Next;
                }
                temp.Next = tmp;
            }
        }
        public void CrushMissile(int Number)
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if(tmp.GetNumber() !=Number)
                    tmp = tmp.Next;
                else if(tmp.GetNumber() == Number)
                {
                    tmp.blive = false;
                    break;
                }
            }
        }
        public int GetMax()
        {
            return MaxNumber;
        }
        public int GetMissileNumber(int Number)
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if (tmp.GetNumber() != Number)
                {
                    tmp = tmp.Next;
                }
                else if (tmp.GetNumber() == Number)
                    break;
            }
            return tmp.MissileNumber;
        }
        public void MissileMove()
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if(tmp != null)
                    tmp.MissileMove();
                else if(tmp == null)
                    break;
                tmp = tmp.Next;
            }
        }
        public int GetMissileX(int number)
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if(tmp.GetNumber() != number)
                {
                    tmp = tmp.Next;
                }
                else if(tmp.GetNumber() == number)
                    break;
            }
            return tmp.GetMissileX();
        }
        public int GetMissileY(int number)
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if(tmp.GetNumber() != number)
                {
                    tmp = tmp.Next;
                }
                else if(tmp.GetNumber() == number)
                    break;
            }
            return tmp.GetMissileY();
        }
        public int GetMissileWidth(int number)
        {
            Missile tmp;
            tmp = MissileArr;
            while (true) {
                if (tmp.GetNumber() != number) {
                    tmp = tmp.Next;
                } else if (tmp.GetNumber() == number)
                    break;
            }
            return tmp.missile_width;
        }
        public int GetMissileHeight(int number)
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if(tmp.GetNumber() != number)
                {
                    tmp = tmp.Next;
                }
                else if(tmp.GetNumber() == number)
                    break;
            }
            return tmp.missile_width;
        }
        public Bitmap GetMissileBitmap(int Number)
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if(tmp.GetNumber() !=Number)
                    tmp = tmp.Next;
                else if(tmp.GetNumber()== Number)
                    break;
            }
            return tmp.GetBitmap();
        }
        public boolean GetMissileLive(int Number)
        {
            Missile tmp;
            tmp = MissileArr;
            while(true)
            {
                if(tmp.GetNumber() !=Number)
                    tmp = tmp.Next;
                else if(tmp.GetNumber() == Number)
                    break;
            }
            return tmp.blive;
        }
    }
    public class Missile
    {
        int mx;
        int my;
        int missile_width;
        boolean blive;
        Missile Next;
        int MissileNumber;
        Bitmap MissileBitmap;
        public Missile()//생상자
        {
            missile_width = 14;
            Next = null;
            blive = true;
        }
        public void CreateMissile(int Number, int sapcex, int sapcey)
        {
            MissileBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.missile0);
            mx=sapcex+60;
            my=sapcey;
            MissileBitmap = Bitmap.createScaledBitmap(MissileBitmap,missile_width,missile_width,true);

            MissileNumber = Number;
        }

        public Missile SetNext(Missile Node)
        {
            if(Node.Next == null)
            {
                return Node;
            }
            else if(Node.Next !=null)
            {
                SetNext(Node.Next);
            }
            return Node;//?
        }
        public void MissileMove()
        {
            if(my >-10)
                my -=5;
        }
        public int GetMissileX()
        {
            return mx;
        }
        public int GetMissileY()
        {
            return my;
        }
        public int GetNumber()
        {
            return MissileNumber;
        }
        public Missile GetNext(Missile Node)
        {
            return Node.Next;
        }
        public Bitmap GetBitmap()
        {
            return MissileBitmap;
        }
    }

    //Thread class
    public class MyThread extends Thread
    {
        public MyThread(SurfaceHolder holder, Context context)
        {
            mHolder = holder;
            mContext = context;

//연산부분
        }
        public void drawEverything(Canvas canvas)
        {
            Paint p1 = new Paint();
            int x;
            int y;
            int mnumber =0;//미사일 임시 넘버
            int pnumber =0;//플랫트 임시 넘버
            p1.setColor(Color.RED);
            p1.setTextSize(50);
            canvas.drawBitmap(screen, 0, 0, p1);
            //if(ship.GetShiplive() ==true)
            canvas.drawBitmap(ship.GetShipBitmap(),ship.GetShipX(),ship.GetShipY(),p1);
//버튼들을 그림
            canvas.drawBitmap(leftKey, leftKeyPosX,leftKeyPosY,p1);
            canvas.drawBitmap(rightKey, rightKeyPosX, rightKeyPosY,p1);
            canvas.drawBitmap( missilebutton, missileKeyPosX, missileKeyPosY,p1);
            if(PlanetList.GetMax() !=0)
            {
                while(true)
                {
                    if(PlanetList.GetMax() == pnumber)
                        break;
                    x = PlanetList.GetX(pnumber);
                    y = PlanetList.GetY(pnumber);
                    if(PlanetList.GetPlanetLive(pnumber)== true)
                        canvas.drawBitmap(PlanetList.GetPlanetBitmap(pnumber),x, y , p1 );
                    pnumber++;
                }
            }
            if(MissileList.GetMax() !=0) {
                while(true)
                {
                    if(MissileList.GetMax() ==mnumber)
                        break;
                    x=MissileList.GetMissileX(mnumber);
                    y=MissileList.GetMissileY(mnumber);
                    if(MissileList.GetMissileLive(mnumber)== true)
                        canvas.drawBitmap(MissileList.GetMissileBitmap(mnumber), x, y, p1);
                    mnumber++;
                }
            }
            String numStr = String.valueOf(ship.Score);
            System.out.println("Score : "+numStr);
            canvas.drawText(numStr, 100,200,p1);
        }
        public void run()
        {
            TimerTask TT = new TimerTask() {
                @Override
                public void run()
                {
                    PlanetList.CreatePlanet();
                }
            };
            timer.schedule(TT,0,500);
            TimerTask MTT = new TimerTask() {
                @Override
                public void run()
                {
                    if(ship.blive ==true)
                        ship.ShipScore(10);
                }
            };
            ScoreTimer.schedule(MTT,0,1000);
            Canvas canvas = null;// 캔버스객체를 생성한다. 캔버스는 도화지이다.
            int number = 0;
            while(true) //반복문
            {
                canvas = mHolder.lockCanvas();//서피스에 픽셀을 나타낼 수 있다.
                //이 메서드를 이용해서 서피스에 lock을 걸고 동작을 수행한다.
                try
                {
                    if(PlanetList.GetMax() !=0)
                    {
                        PlanetList.Move();
                        if(PlanetList.Crush(ship.GetShipX(),ship.GetShipY(),ship.GetWidth(),ship.GetHeight()) == true)
                        {//rect.contains();
                            ship.Crush();
                            if(ship.blive ==false)
                            {
                                //((MainActivity)mContext).Box(ship.GetScore());
                              break;
                               //finishAffinity();
                               // android.os.Process.killProcess(android.os.Process.myPid());
                                //moveTaskToBack(true);
                                 //finish();
                                //system.exit(0)
                            }
                        }
                        while(true)
                        {
                            if(MissileList.GetMax() == 0)
                            {
                                number =0;
                                break;
                            }
                            else if (MissileList.GetMax() != 0)
                            {
                                if (number == MissileList.GetMax())
                                {
                                    number =0;
                                    break;
                                }
                                if(MissileList.GetMissileLive(number)== true)
                                {
                                    if (PlanetList.Crush(MissileList.GetMissileX(MissileList.GetMissileNumber(number)), MissileList.GetMissileY(MissileList.GetMissileNumber(number)), MissileList.GetMissileWidth(number) ,MissileList.GetMissileHeight(number)) == true)
                                    {
                                        MissileList.CrushMissile(number);
                                        if(ship.blive ==true)
                                            ship.ShipScore(100);
                                    }
                                }
                                number++;
                            }
                        }
                    }
                    if(MissileList.GetMax() !=0)
                    {
                        MissileList.MissileMove();
                    }
                    synchronized (mHolder)
                    {
                        drawEverything(canvas);//모든 픽셀을 서피스에 표현한다.(반복하면서)
                    }
                }
                finally//빠저 나가는게 아니라 이 코드에 오면 무조건 실행
                {
                    if(canvas != null)
                    {
                        mHolder.unlockCanvasAndPost(canvas);//실제화면에 복사한다.
                        //서피스(?)에 진행하는 행동을 멈추고
                        //실제화면으로 복하한다.
                    }
                }
            }
            ((MainActivity)mContext).Box(ship.GetScore());
        }
    }
    @Override//마우스 입력
    public boolean onTouchEvent(MotionEvent event) {
        if(event.getAction() == MotionEvent.ACTION_DOWN|| event.getAction() == MotionEvent.ACTION_MOVE)
        {
            touchPosX = (int)event.getX();
            touchPosY = (int)event.getY();
        }

//왼존키를 터치햇을때
        if((touchPosX >leftKeyPosX) &&(touchPosX <leftKeyPosX+button_width) && (touchPosY>leftKeyPosY)&&(touchPosY<leftKeyPosY+button_width))
        {
//spaceshipPosX-=20;
            if(ship.GetShiplive() ==true)
                ship.SpaceshipMove(0);
        }
//오른쪽키를 터치했을때
        if((touchPosX > rightKeyPosX) && (touchPosX < rightKeyPosX + button_width) && (touchPosY > rightKeyPosY) && (touchPosY < rightKeyPosY + button_width))
        {
//spaceshipPosX+=20;
            if(ship.GetShiplive() ==true)
                ship.SpaceshipMove(1);
        }
        if((touchPosX > missileKeyPosX) && (touchPosX < missileKeyPosX + button_width) && (touchPosY > missileKeyPosY) && (touchPosY < missileKeyPosY + button_width))
        {
            ((MainActivity)mContext).Box(ship.GetScore());
            if(ship.GetShiplive() ==true)
                MissileList.CreateMissile(ship.GetShipX(),ship.GetShipY());
        }
        invalidate();
        return true;//제대로 처리되었을경우 true 반환/ 없을시 에러발생
    }

}

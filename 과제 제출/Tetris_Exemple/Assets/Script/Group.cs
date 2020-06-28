
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Group : MonoBehaviour
{

    private float DropTime = 0f;
    private bool b_move = true;
    public List<Transform> list = new List<Transform>();

    public enum KeyNum
    {
        DOWN = 0,
        LEFT = 1,
        RIGHT = 2,
    };
    private void OnEnable()
    {
        Transform t;
        string str;
        DropTime = 0f;
        for (int i = 1; i < 5; i++)
        {
            str = "Block" + i;
            t = transform.Find(str);
            list.Add(t);
        }
    }

    public bool CheckInScreen(KeyNum key, List<Transform> list)
    {
        int count = 0;
        Vector2 vtmp;//벡터(위치)를 담을 임시 공간
        if (key == KeyNum.RIGHT || key == KeyNum.LEFT)
        {
            Vector2 vx = new Vector2(1, 0);//x축으로 줄 변화값에 대한 벡터
            for (int i = 0; i < 4; i++)
            {
                Transform Ttmp = list[i];//만약의 사태를 위해서 list 대신 Ttmp에 변화를 주는 방식
                Vector2 v = Ttmp.position;//v에 Ttmp(block)의 위치값 설정 
                if (key == KeyNum.RIGHT)
                {
                    vtmp = v + vx;//오른쪽 방향이기에 증가
                    if (10 > vtmp.x && Field.grid[(int)vtmp.x, (int)vtmp.y] == null)
                        count++;//조건을 충족한다면 count증가
                    else
                        return false;//조건에 하나라도 충족못한다면 이동 못하도록 false값 return
                }//이동할 각 block의 좌표가 최댓값 10 미만이여야 하고(AND) 이동할 위치에 다른 block이 없어야 한다.
                else if (key == KeyNum.LEFT)
                {
                    vtmp = v - vx;//왼쪽 방향이기에 감소
                    if (-1 < vtmp.x && Field.grid[(int)vtmp.x, (int)vtmp.y] == null)
                        count++;
                    else
                        return false;
                }
            }
            if (count == 4)//count가 4일때 group객체의 모든 block이 조건을 충족해서 
                return true;//이동할수 있도록 true를 return 한다.
        }
        else if (key == KeyNum.DOWN)
        {
            Vector2 vy = new Vector2(0, 1);
            for (int i = 0; i < 4; i++)
            {
                Transform Ttmp = list[i];
                Vector2 v = Ttmp.position;
                vtmp = v - vy;
                if (Field.grid[(int)vtmp.x, (int)vtmp.y] == null)
                    count++;
                else
                    break;
            }
            // (Field.grid[(int)vtmp.x, (int)vtmp.y] == null || vtmp.y <= 0)//&&하면 조건식vtmp.y <= 0이걸려서 작동하지 않음
            // vtmp.y <= 0자체가 필요 없는듯(왜 있는지 의아하기도 했음 사실)
            if (count == 4)
                return true;
        }
        return false;//키를 안눌렸거나 그냥 지나가는 코드 일경우를 대비해서 
        //bool 반환형이 있기에 마지막에 나갈 부분을 준비해야 한다.
    }

    public void InputKey(List<Transform> list)
    {
        //1
        if (Input.GetKeyDown(KeyCode.LeftArrow) && b_move == true)//지정 키를 누른고(AND) 현 Group이 움직이는 상태라면
        {
            if (CheckInScreen(KeyNum.LEFT, list) == true)//ChekcInScreen이 true를 반환했다면(이동 가능하다면)
                transform.position -= new Vector3(1, 0, 0);//객체를 이동(객체의 좌표를 이동시키는 코드)
            //2
        }
        else if (Input.GetKeyDown(KeyCode.RightArrow) && b_move == true)
        {
            if (CheckInScreen(KeyNum.RIGHT, list) == true)
                transform.position += new Vector3(1, 0, 0);
            //3
        }
        else if (Input.GetKeyDown(KeyCode.DownArrow) && b_move == true)
        {
            if (CheckInScreen(KeyNum.DOWN, list) == true)
                transform.position -= new Vector3(0, 1, 0);
            //4
        }
        //회전
        else if (Input.GetKeyDown(KeyCode.R) && b_move == true)
        {
            if (CheckRotation(list) == true)
                transform.Rotate(0, 0, -90);
        }
    }
    public bool CheckRotation(List<Transform> list)
    {
        Transform tmp = transform;
        tmp.Rotate(0, 0, -90);
        for (int i = 0; i < 4; i++)
        {
            Vector2 vtmp = list[i].position;
            vtmp = Field.roundVec2(vtmp);
            if (10 <= vtmp.x)
            {
                tmp.Rotate(0, 0, +90);
                return false;
            }
            else if (0 > vtmp.x)
            {
                tmp.Rotate(0, 0, +90);
                return false;
            }
            if (0 >= vtmp.y)
            {
                tmp.Rotate(0, 0, +90);
                return false;
            }
            if (Field.grid[(int)vtmp.x, (int)vtmp.y] != null)
            {
                tmp.Rotate(0, 0, +90);
                return false;
            }
        }
        tmp.Rotate(0, 0, +90);
        return true;
    }
    public void TouchGround()
    {

        bool bCheckCollider = false;
        bool bTouchGround = false;
        Vector2 vtmp;//벡터 임시 저장소
        Vector2 vy = new Vector2(0, 1);
        for (int i = 0; i < 4; i++)
        {
            Transform Ttmp = (Transform)list[i];
            Vector2 v = Ttmp.position;
            if (v.y == 0)//하나라도 땅에 닿으면
                bTouchGround = true;
        }
        if (bTouchGround == true)
        {
            for (int i = 0; i < 4; i++)
            {
                Transform Ttmp = (Transform)list[i];
                Vector2 v = Ttmp.position;
                v = Field.roundVec2(v);
                Field.grid[(int)v.x, (int)v.y] = list[i];
            }
            Field.CheckFullLine();
            enabled = false;//작동 정지
            b_move = false;//작동정지 확인용 
            if (GameManager.instance != null && GameManager.instance.m_bGameover == false)
                FindObjectOfType<Spawner>().NewSpawn();
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                Transform Ttmp = (Transform)list[i];
                Vector2 v = Ttmp.position;
                v = Field.roundVec2(v);
                vtmp = v - vy;
                if (v.y <= 0)// 하나라도 0에 닿으면
                {
                    bCheckCollider = true;
                    break;
                }
                else if (Field.grid[(int)vtmp.x, (int)vtmp.y] != null)
                {
                    bCheckCollider = true;
                    break;
                }
            }
            if (bCheckCollider == true)
            {
                for (int i = 0; i < 4; i++)
                {
                    Transform Ttmp = (Transform)list[i];
                    Vector2 v = Ttmp.position;
                    v = Field.roundVec2(v);
                    Field.grid[(int)v.x, (int)v.y] = list[i];
                }
                Field.CheckFullLine();
                TouchCeiling();
                enabled = false;//작동 정지
                b_move = false;//작동정지 확인용 
                if (GameManager.instance != null && GameManager.instance.m_bGameover == false)
                    FindObjectOfType<Spawner>().NewSpawn();
            }
        }
    }

    public void TouchCeiling()
    {
        for (int i = 0; i < 4; i++)
        {
            Transform Ttmp = (Transform)list[i];
            Vector2 v = Ttmp.position;
            v = Field.roundVec2(v);
            if (v.y >= 15)
            {
                if (GameManager.instance.m_bGameover == false)
                    GameManager.instance.Active_GameOver();
            }
        }
    }
    void Update()
    {
        if (GameManager.instance.m_bGameover == false && Stage.m_bStageOn == false)
        {
            //5
            //방향키 사용한 이동 코드
            InputKey(list);
            //6
            TouchGround();
            //1타임 차이마다 1칸씩 아래로 이동 - 지속사용이라 큰 문제가 없이 작동
            if (Time.time - DropTime >= 1 && b_move == true)
            {
                transform.position -= new Vector3(0, 1, 0);
                DropTime = Time.time;
            }
            //7
        }
    }
}
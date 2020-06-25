
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Field : MonoBehaviour
{
    public static int width = 10;
    public static int height = 20;

    // Start is called before the first frame update
    public static Transform[,] grid = new Transform[width, height];

    public static Vector2 roundVec2(Vector2 v)
    {
        //Vector2(1.02934, 2.3498) => Vector2(1, 2)로 보정해준다.
        return new Vector2(Mathf.Round(v.x), Mathf.Round(v.y));
    }
    public static void CheckFullLine()
    {
        int CheckCount = 0;
        // List<int> DeleteLine = new List<int>();
        //int DeleteCount = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (grid[x, y] != null)
                {
                    CheckCount++;
                    if (CheckCount == 10)//한줄이 완성되었을때
                    {
                        DestroyLine(y);
                        ReFillLine(y);
                        //CheckCount = 0;
                        y--;//한줄 내려가서 인식이 안됨
                            //DeleteCount++;//삭제가 이루어지면 카운터증가
                            // DeleteLine.Add(y);//삭제된 라인 값 저장
                    }
                }
                //한줄을 다 확인했지만 한줄이 완성이 안되었을때
                //else if (x == width - 1 || grid[x, y] == null)
                //    CheckCount = 0;
            }
            CheckCount = 0;//한 줄 탐색 끝나면 카운터 초기화
        }
        //if (DeleteCount != 0)
        //    ReFillLine(y);
    }
    //줄 삭제 메서드
    public static void DestroyLine(int y)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[x, y] != null)
            {
                Destroy(grid[x, y].gameObject);
                grid[x, y] = null;
            }
        }
        GameManager.instance.UpdateScore(100);
    }
    public static void ReFillLine(int Line)//List<int> list, int count
    {
      //1
        for (int y = Line; y < height - 1; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (grid[x, y + 1] != null)
                {
                    grid[x, y] = grid[x, y + 1];
                    grid[x, y + 1] = null;
                    grid[x, y].position -= new Vector3(0, 1, 0);
                }
            }
        }

    }
    void Start()
    {

    }
    public static void AllDelete()//클리어, 스테이지 통과, 게임오버시? 재시작시
    {
        int point = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (grid[x, y] != null)
                {
                    Destroy(grid[x, y].gameObject);
                    grid[x, y] = null;
                    point++;
                }
            }
        }
        point = point * 100;//스테이지 클리어시 추가 점수
    }
    // Update is called once per frame
    void Update()
    {
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class obstacle : MonoBehaviour
{
    public GameObject Obstacle;
    public void CreateObstacle(int stage)
    {
        int ObstacleCount;
        int CreateWidth;
        int CreateHeight = 0;
        GameObject g = Instantiate(Obstacle);//장애물 오브젝트 생성
        if (stage == 0)
            return;
        else
        {
            ObstacleCount = stage * 3;
            for (int i = 0; i < ObstacleCount; i++)//장애물 갯수만큼 생성
            {
                CreateHeight = Random.Range(0, 6);
                CreateWidth = Random.Range(0, 10);
                if (Field.grid[CreateWidth, CreateHeight] != null)
                {
                    while (true)
                    {
                        CreateHeight = Random.Range(0, 6);
                        CreateWidth = Random.Range(0, 10);
                        if (Field.grid[CreateWidth, CreateHeight] == null)
                            break;
                    }
                }
                Vector2 v = new Vector2(CreateWidth, CreateHeight);
                g.transform.position = v;
                v = Field.roundVec2(v);
                Instantiate(g, g.transform.position, Quaternion.identity);
                Field.grid[(int)v.x, (int)v.y] = g.transform;
            }
        }
    }
}
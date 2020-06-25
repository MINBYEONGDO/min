
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class obstacle : MonoBehaviour
{
    public GameObject Obstacle;
    void Start()
    {

    }
    public void CreateObstacle(int stage)
    {
        int ObstacleCount;
        int CreateWidth;
        int CreateHeight = 0;
        GameObject g = Instantiate(Obstacle);
        //g = Obstacle;
        Transform t;
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
                t = g.transform;

                Vector2 v = new Vector2(CreateWidth, CreateHeight);
                t.transform.position = v;
                v = Field.roundVec2(v);
                Instantiate(t, t.transform.position, Quaternion.identity);
                Field.grid[(int)v.x, (int)v.y] = t.transform;
            }
        }
    }
    void Update()
    {

    }
}
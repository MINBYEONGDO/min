
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreRankText : MonoBehaviour
{
    public Text ScoreText;//Score Text Prefab
    public static List<int> GameScoreList;//json에 저장된 과거 스코어 전적

    public void ScoreRank()
    {
        if (GameScoreList != null)//재시작시
            GameScoreList.Clear();
        else if (GameScoreList == null)//처음 시작시
            GameScoreList = new List<int>();

        GameScoreList = JsonData.LoadScore();
        int num = GameScoreList.Count;//list의 길이 저장
        for (int i = 0; i < num; i++)
        {
            ScoreText.text = i + 1 + "st" + GameScoreList[i];
            Text t = Instantiate(ScoreText, ScoreText.transform.position, Quaternion.identity);
            //t.transform.parent = transform;//이거쓰면 경고문 뜸 ㅠ 그래서 setParent사용
            t.transform.SetParent(transform);//생성한 ScoreText의 부모를 현재 GameObject인 ScoreRankText로 설정
            t.transform.localPosition = new Vector3(0, 80 - i * 20, 0);//상속관계로 localPosition으로 위치 설정
        }
    }
}
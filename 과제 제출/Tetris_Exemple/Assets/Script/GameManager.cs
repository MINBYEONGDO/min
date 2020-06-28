
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{

    public List<int> GameScoreList;
    public bool m_bGameover = false;
    static public int mScore = 0;
    public string RestartKey = "Restart";
    public GameObject SubMenu;
    static private GameManager GM_instance;
    public static GameManager instance
    {
        get
        {
            if (GM_instance == null)
                GM_instance = FindObjectOfType<GameManager>();
            return GM_instance;
        }
    }
    public void OnEnable()
    {
        ScoreLoad();
    }
    public void ScoreLoad()
    {
        if (GameScoreList != null)
            GameScoreList.Clear();
        else if (GameScoreList == null)
            GameScoreList = new List<int>();
        GameScoreList = JsonData.LoadScore();
    }
    private void Awake()
    {
        if (instance != this)
            Destroy(gameObject);
        m_bGameover = false;
    }
    public void UpdateScore(int Score)
    {
        mScore += Score;
    }
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (SubMenu.activeSelf == true)
            {
                SubMenu.SetActive(false);
                OnApplicationPause(false);
            }
            else
            {
                SubMenu.SetActive(true);
                OnApplicationPause(true);
            }
        }
        UIManager.instance.UpdateScore(mScore);
        if (Input.GetButtonDown(RestartKey) && m_bGameover == true)
        {
            UIManager.instance.ReStart();
        }
    }
    private void OnApplicationPause(bool pause)
    {
        if (pause)
            Time.timeScale = 0;
        else
            Time.timeScale = 1;
    }
    public void Active_GameOver()
    {
        //GameScoreList = FindObjectOfType<ScoreRankText>().;
        //GameScoreList = ScoreRankText.GameScoreList;
        m_bGameover = true;
        UIManager.instance.SetActiveGameOverUI();
        GameScoreList.Add(mScore);
        JsonData.SaveScore(GameScoreList);
    }
}
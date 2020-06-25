
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class UIManager : MonoBehaviour
{

    public Text ScoreText;
    public GameObject gameoverUI;
    public GameObject NextGroupImage;
    // List<Transform> glist;
    private static UIManager minstance;
    public static UIManager instance
    {
        get
        {
            if (minstance == null)
            {
                minstance = FindObjectOfType<UIManager>();
            }
            return minstance;
        }
    }
    public void UpdateScore(int Score)
    {
        ScoreText.text = "Score : " + Score;
    }

    public void NextGroup(int Number)
    {
        string str = "Group" + Number;
        foreach (Transform t in NextGroupImage.transform)
        {
            if (t.gameObject.activeSelf == true)//활성화 비활성화 확인
                t.gameObject.SetActive(false);
            if (t.name == str)
                t.gameObject.SetActive(true);
        }
    }
    public void SetActiveGameOverUI()
    {
        gameoverUI.SetActive(true);
    }

    public void ReStart()//게임매니저로 이동
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
    void Start()
    {
    }

    void Update()
    {
    }
}
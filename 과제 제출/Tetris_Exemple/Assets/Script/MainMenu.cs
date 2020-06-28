
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class MainMenu : MonoBehaviour
{

    public GameObject ScoreText;
    public void PlayGame()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex - 1);
    }
    public void ScorePanel()
    {
        ScoreText.SetActive(true);
        FindObjectOfType<ScoreRankText>().ScoreRank();
        GetComponentInParent<ScoreRankText>().ScoreRank();
    }
    public void QuitGame()
    {
        Application.Quit();
    }
}


using UnityEngine;

public class TerrainDrying : MonoBehaviour
{
    public Material wetDirtMaterial;
    public Material dryDirtMaterial;
    public Material crackedDirtMaterial;
    public Renderer terrainRenderer;

    private float dryingFactor = 0f; // 0 is fully wet, 1 is fully dry
    private float dryingRate = 0.1f; // The rate at which the terrain dries

    void Update()
    {
        // Update the drying factor based on the drying rate
        dryingFactor += Time.deltaTime * dryingRate;
        dryingFactor = Mathf.Clamp01(dryingFactor);

        // Lerp between the materials based on the drying factor
        if (dryingFactor < 0.5f)
        {
            // Transition from wet to dry
            terrainRenderer.material.Lerp(wetDirtMaterial, dryDirtMaterial, dryingFactor * 2f);
        }
        else
        {
            // Transition from dry to cracked
            terrainRenderer.material.Lerp(dryDirtMaterial, crackedDirtMaterial, (dryingFactor - 0.5f) * 2f);
        }
    }
}

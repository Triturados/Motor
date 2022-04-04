function escenaEjemplo()
    IvanTontoTonto()
end

function scene0()
    scene:name("Escena de Daniel")
    
    local suelo = scene:createObject("Suelo")
    local comp = suelo:addComponent("EscribirNumero")
    local comp2 = suelo:addComponent('Transform')
    
    comp2:sendMsg([[
        scale: 50,1,50;
        position: 0,0,0;
        rotation: 0,0,0,0;
    ]])
    local comp3 = suelo:addComponent('Mesh'):sendMsg([[
        meshName: cube.mesh;
    ]])

    local camaraAidaLaMejor = scene:createObject("CamaritaGuapa")
    local compAidaLaMejor = camaraAidaLaMejor:addComponent('Transform')
        
    compAidaLaMejor:sendMsg([[
        scale: 1,1,1;
        position: 0,10,50;
        rotation: 0,0,0,0;
    ]])
    local compAidaLaMejor2 = camaraAidaLaMejor:addComponent('Camera')
   

    -- local comp4 = suelo:addComponent("Rigidbody")
end


function scene1()
    scene:name("Escena de Dani")
    local obj = scene:createObject("Objeto de Dani")
    --obj:addComponent("ComponenteDeContar"):sendMsg("Hola tontatatatata")
    --obj:addComponent("MouseTracker")
    obj:addComponent('EscribirNumero'):sendMsg([[
        numerito: 4;
        otronumerito: 12 
    ]])
end



-- function scene2()
--     scene::name("Calvo cabron")
--     -- local suelo = scene:createObject("Suelo")
--     -- local comp = suelo:addComponent("EscribirNumero")
--     -- local comp2 = suelo:addComponent("Transform")
    
--     -- local comp3 = suelo:addComponent("Mesh"):sendMsg([[
--     --     meshName: cube.mesh
--     -- ]])
--     -- local comp4 = suelo:addComponent("Rigidbody")
--     comp4:
-- end
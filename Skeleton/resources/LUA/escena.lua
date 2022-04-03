function escenaEjemplo()
    IvanTontoTonto()
end


function scene0()
    scene:name("Escena de Dani")
    local obj = scene:createObject("Objeto de Dani")
    --obj:addComponent("ComponenteDeContar"):sendMsg("Hola tontatatatata")
    --obj:addComponent("MouseTracker")
    obj:addComponent('EscribirNumero'):sendMsg([[
        numerito: 4;
        otronumerito: 12 
    ]])
end


function scene1()
    scene:name("Escena de Daniel")
    local obj = scene:createObject("Objeto de Daniel")
    local comp = obj:addComponent("EscribirNumero")
    comp:send2(1, 0)
end

function scene2()
    scene::name("Calvo cabron")
    local suelo = scene:createObject("Suelo")
    local comp = suelo:addComponent("EscribirNumero")
    local comp2 = suelo:addComponent("Transform")
    
    local comp3 = suelo:addComponent("Mesh"):sendMsg([[
        meshName: cube.mesh
    ]])
    local comp4 = suelo:addComponent("Rigidbody")
    comp4:
end
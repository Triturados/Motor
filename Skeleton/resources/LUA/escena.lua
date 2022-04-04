function escenaEjemplo()
    IvanTontoTonto()
end

function scene0()
    scene:name("Escena de Prueba")
    
    local suelo = scene:createObject("Suelo")
    local comp2 = suelo:addComponent("Transform")
    
    comp2:sendMsg([[
        scale: 50,1,50;
        position: 0,0,0;
        rotation: 0,0,0,0;
    ]])

    local comp3 = suelo:addComponent("Mesh"):sendMsg([[
        meshName: cube.mesh;
    ]])
    local compRigidbodySuelo = suelo:addComponent('Rigidbody')
    compRigidbodySuelo:send2(0, 0.0)
    compRigidbodySuelo:sendMsg([[forma: cube]])

    local camaraAidaLaMejor = scene:createObject("CamaritaGuapa")
    local compAidaLaMejor = camaraAidaLaMejor:addComponent('Transform')
        
    compAidaLaMejor:sendMsg([[
        scale: 1,1,1;
        position: 0,30,200;
        rotation: 0,0,0,0;
    ]])
    local compAidaLaMejor2 = camaraAidaLaMejor:addComponent('Camera')
   
    local bola = scene:createObject("Bola")
    local compBola = bola:addComponent('Transform')
        
    compBola:sendMsg([[
        scale: 1,1,1;
        position: 0,20,0;
        rotation: 0,0,0,0;
    ]])
    local compBolaMesh = bola:addComponent('Mesh'):sendMsg([[
        meshName: sphere.mesh;
    ]])

    local compRigidbody = bola:addComponent('Rigidbody')
    compRigidbody:send2(0, 1.0)
    compRigidbody:sendMsg([[forma: sphere]])

    local luz = scene:createObject("Luz")
    local compLuz = luz:addComponent('Transform')
        
    compLuz:sendMsg([[
        scale: 1,1,1;
        position: 0,40,0;
        rotation: 0,0,0,0;
    ]])

    local compLight = luz:addComponent('Light')
    compLight:send2(0, 0.0)

   local player = scene:createObject("jugador")
   local tr = player:addComponent("Transform")
   tr:sendMsg([[
    scale: 2,2,2;
    position: 0,20,0;
    rotation: 0,0,0,0;
]])
local mesh = player:addComponent("Mesh")
mesh:sendMsg([[meshName: Sinbad.mesh]])
player:addComponent("MovimientoJugador"):sendMsg([[
    speed: 15.0
    rotSpeed: 5.0
]])
    
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

function scene2()
    scene:name("Escena de Daniel")
    
    local suelo = scene:createObject("Suelo")
    local comp = suelo:addComponent("EscribirNumero")
    local comp2 = suelo:addComponent("Transform")
    
    comp2:sendMsg([[
        scale: 50,1,50;
        position: 0,-100,0;
        rotation: 0,0,0,0;
    ]])
    local comp3 = suelo:addComponent("Mesh"):sendMsg([[
        meshName: cube.mesh;
    ]])

    local camaraAidaLaMejor = scene:createObject("CamaritaGuapa")
    local compAidaLaMejor = camaraAidaLaMejor:addComponent("Transform")
        
    compAidaLaMejor:sendMsg([[
        scale: 1,1,1;
        position: 0,10,50;
        rotation: 0,0,0,0;
    ]])
    local compAidaLaMejor2 = camaraAidaLaMejor:addComponent("Camera")
   

    -- local comp4 = suelo:addComponent("Rigidbody")
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